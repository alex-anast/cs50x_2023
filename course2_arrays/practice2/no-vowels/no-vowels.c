// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string input);

int main(int argc, string argv[])
{
    /* must accept a single command-line argument */ 
    if (argc != 2)
    {
        printf("wrong input\n");
        return 1;
    }
    
    printf("%s", replace(argv[1]));
}

string replace(string word)
{
    /* define the string-holder variable */
    string result = word;

    /* define the length for minimizing overhead */
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        /* ensure that the same effect will happen in uppercase too */
        switch (tolower(word[i]))
        {
            case 'a':
                result[i] = '6';
                /* break is for the switch-case statement */
                break;
            case 'e':
                result[i] = '3';
                break;
            case 'i':
                result[i] = '1';
                break;
            case 'o':
                result[i] = '0';
                break;
        }
    }

    /* return the converted single word */
    return result;
}
