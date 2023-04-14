#include <cs50.h>
#include <stdio.h>
#include <string.h> // strncmp
#include <stdlib.h> // atoi

enum Company
{
    INVALID = 0,
    AMEX,
    MASTERCARD,
    VISA
};

int is_amex(char* card_number);
int is_mastercard(char* card_number);
int is_visa(char* card_number);
int luhn_algorithm(long card_number);
enum Company find_company(long answer);
enum Company card_info(long answer);

int main(void) 
{
    long answer = get_long("Type your card number: ");

    enum Company company = card_info(answer);

    switch (company) {
        case AMEX:
            printf("AMEX\n");
            break;
        case MASTERCARD:
            printf("MASTERCARD\n");
            break;
        case VISA:
            printf("VISA\n");
            break;
        default:
            printf("INVALID\n");
            break;
    }
}

int luhn_algorithm(long card_number)
{
    int total_sum = 0;
    int num_digits = 0;

    /* loop through each digit of the card number from right to left */
    while (card_number > 0)
    {
        /* get the last digit of the card number */
        int digit = card_number % 10;

        /* if the digit is in an odd position (counting from the right) */
        if (num_digits % 2 == 1)
        {
            /* multiply the digit by 2 */
            int product = digit * 2;

            /* add the digits of the product together */
            while (product > 0)
            {
                total_sum += product % 10;
                product /= 10;
            }
        }
        /* if the digit is in an even position (counting from the right) */
        else
        {
            total_sum += digit;
        }

        /* move on to the next digit of the card number */
        card_number /= 10;
        num_digits++;
    }

    /* if the last digit of the total sum is 0, the card number is valid */
    if (total_sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* I don´t like booleans in C */
int is_amex(char* card_number)
{
    if (strncmp(card_number, "34", 2) == 0 || strncmp(card_number, "37", 2) == 0)
    {
        return 1;
    }
    return 0;
}

int is_mastercard(char* card_number) {
    char prefix_str[3];
    /* copy the first two characters */
    strncpy(prefix_str, card_number, 2);
    /* set end-of-string */
    prefix_str[2] = '\0';
    /* convert to integer (ASCII to integer) */
    int prefix = atoi(prefix_str);
    /* check if is_mastercard */
    if (prefix >= 51 && prefix <= 55)
    {
        return 1;
    }
    return 0;
}

int is_visa(char* card_number)
{
    if (card_number[0] == '4')
    {
        return 1;
    }
    return 0;
}

// enum Company find_company(answer)
enum Company find_company(long answer)
{
    /* create buffer for the string to come */
    char card_number[20];
    /* convert long to strign */
    sprintf(card_number, "%ld", answer);

    if (is_amex(card_number))
    {
        return 1;
    }
    else if (is_mastercard(card_number))
    {
        return 2;
    }
    else if (is_visa(card_number))
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief retrieves information about the card number
 * 
 * @param answer 
 * @return enum Company 
 */
enum Company card_info(long answer)
{
    /* returns whether the card is valid */
    int is_valid = luhn_algorithm(answer);

    if (is_valid)
    {
        return find_company(answer);
    }
    else
    {
        /* return 0 (from enum) */
        return INVALID;
    }
}
