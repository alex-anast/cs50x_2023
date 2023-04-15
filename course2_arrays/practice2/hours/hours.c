#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

/* complete the calc_hours function */
float calc_hours(int hours[], int weeks, char output)
{
    /* initialize a var for the total amount of hours */
    int total_hours = hours[0];
    /* the first input (should always exist) has already been added */
    for (int i = 1; i < weeks; i++)
    {
        /* add every input to the total sum */
        total_hours += hours[i];
    }

    if (output == 'A')
    {
        return (total_hours / (float) weeks);
    }
    else if (output == 'T')
    {
        return total_hours;
    }
    /* unreachable code, but just in case */
    else
    {
        printf("Error: invalid output type\n");
        return 0;
    }
}
