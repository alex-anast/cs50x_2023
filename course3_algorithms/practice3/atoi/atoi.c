#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

/**
 * @brief 
 *        
 * 
 * @param input 
 * @return int 
 */
int convert(string input)
{
    int integer_value;

    /* convert last char into an integer value */
    integer_value = (int)(input[strlen(input)-1]) - 48;

    /* base caseL if no need to go into the recersion (if string is only one char) */
    if (strlen(input) == 1)
    {
        return integer_value;
    }

    /* Then shorten the string and recursively call */
    input[strlen(input) - 1] = '\0';
    
    /* whatever it is, but in 10 times scale + the last calculated */
    return 10 * convert(input) + integer_value;
}
