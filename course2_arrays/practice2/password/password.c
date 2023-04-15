// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_lowercase(string password);
int check_uppercase(string password);
int check_number(string password);
int check_symbol(string password);
int valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

/* returns true if password is okay, or else returns false */
int valid(string password)
{
    /* readability > one-liners */
    return (                         \
        check_lowercase(password) && \
        check_uppercase(password) && \
        check_number(password)    && \
        check_symbol(password)       \
        );
}

/* check if string contains a lowercase */
int check_lowercase(string password)
{
    /* loop through the string */
    for (int i = 0, length = strlen(password); i < length; i++)
    {
        /* check with the help of ctype.h */
        if (islower(password[i]))
        {
            /* not an error code; returns the equivalent <true>, C99 doesn´t have booleans */
            return 1;
        }
    }
    /* if not found, return false */
    return 0;
}

/* check if string contains uppercase */
int check_uppercase(string password)
{
    /* loop through the string */
    for (int i = 0, length = strlen(password); i < length; i++)
    {
        /* check with the help of ctype.h */
        if (isupper(password[i]))
        {
            /* not an error code; returns the equivalent <true>, C99 doesn´t have booleans */
            return 1;
        }
    }
    /* if not found, return false */
    return 0;
}

/* check if string contains number */
int check_number(string password)
{
    /* loop through the string */
    for (int i = 0, length = strlen(password); i < length; i++)
    {
        /* check with the help of ctype.h */
        if (isdigit(password[i]))
        {
            /* not an error code; returns the equivalent <true>, C99 doesn´t have booleans */
            return 1;
        }
    }
    /* if not found, return false */
    return 0;
}

/* check if string contains a symbol == punctuation */
int check_symbol(string password)
{
    /* loop through the string */
    for (int i = 0, length = strlen(password); i < length; i++)
    {
        /* check with the help of ctype.h */
        if (ispunct(password[i]))
        {
            /* not an error code; returns the equivalent <true>, C99 doesn´t have booleans */
            return 1;
        }
    }
    /* if not found, return false */
    return 0;
}
