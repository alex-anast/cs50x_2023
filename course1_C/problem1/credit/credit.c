#include <cs50.h>
#include <stdio.h>
#include <string.h> // strncmp
#include <stdlib.h> // atoi

#define CARD_LENGTH_AMEX        15
#define CARD_LENGTH_MASTERCARD  16
#define CARD_LENGTH_VISA_1      13
#define CARD_LENGTH_VISA_2      16

enum Company
{
    INVALID = 0,
    AMEX,
    MASTERCARD,
    VISA
};

int is_amex(char* card_number, int length);
int is_mastercard(char* card_number, int length);
int is_visa(char* card_number, int length);
int luhn_algorithm(long card_number);
enum Company find_company(long card_number);
enum Company card_info(long card_number);

int main(void) 
{
    long card_number = get_long("Type your card number: ");

    enum Company company = card_info(card_number);

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
    int digit_position = 0;

    /* loop through each digit of the card number from right to left */
    while (card_number > 0)
    {
        /* get the last digit of the card number */
        int digit = card_number % 10;

        /* if the digit is in an odd position (counting from the right) */
        if (digit_position % 2 == 1)
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
        digit_position++;
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

int is_amex(char* card_number, int length)
{
    if (strncmp(card_number, "34", 2) == 0 || strncmp(card_number, "37", 2) == 0)
    {
        if (length == CARD_LENGTH_AMEX)
        {
            return 1;
        }
    }
    return 0;
}

int is_mastercard(char* card_number, int length)
{
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
        if (length == CARD_LENGTH_MASTERCARD)
        {
            return 1;
        }
    }
    return 0;
}

int is_visa(char* card_number, int length)
{
    if (card_number[0] == '4')
    {
        if (length == CARD_LENGTH_VISA_1 || length == CARD_LENGTH_VISA_2)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief return the enum that corresponds to the card´s company
 * 
 * @param card_number 
 * @return enum Company 
 */
enum Company find_company(long card_number_long)
{
    /* create buffer for the string to come */
    /* add one more on purpose to manually terminate */
    char card_number_char[21];
    
    /* convert long to string -> TODO: check for overflow with snprintf */
    sprintf(card_number_char, "%ld", card_number_long);
    card_number_char[20] = '\0';

    /* calculate and pass as parameter to reduce overhead of repeated calculations */
    int card_length = strlen(card_number_char);

    /* if card belongs to American Express */
    if (is_amex(card_number_char, card_length))
    {
        return AMEX;
    }
    /* if card belongs to Mastercard */
    else if (is_mastercard(card_number_char, card_length))
    {
        return MASTERCARD;
    }
    /* if card belongs to VISA */
    else if (is_visa(card_number_char, card_length))
    {
        return VISA;
    }
    /* if card doesn´t belong to any of the companies stated */
    else
    {
        return INVALID;
    }
}

/**
 * @brief retrieves information about the card number
 * 
 * @param card_number 
 * @return enum Company 
 */
enum Company card_info(long card_number)
{
    /* returns 1 if card passes luhn algorithm, else 0 */
    int is_valid = luhn_algorithm(card_number);

    if (is_valid)
    {
        printf("entered\n");
        return find_company(card_number);
    }
    else
    {
        /* return 0 (from enum) */
        return INVALID;
    }
}
