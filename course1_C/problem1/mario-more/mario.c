#include <cs50.h>
#include <stdio.h>

void print_pyramid(int size);

int main(void) 
{
    int size;
    do
    {
        size = get_int("Give height of the pyramid: ");
    }
    /* condition that makes the input correct */
    while (size < 1 || size > 8);

    /* "pseudocode" */
    print_pyramid(size);

    return 0;
}

void print_pyramid(int size)
{
    /* for each line */
    for (int i = 0; i < size; i++)
    {
        /**print spaces before hashes;
         * it refers to the line number as reference
         */
        for (int j = 0; j < size - i - 1; j++) {
            printf(" ");
        }
        
        /* print hashes; again line no as reference */
        for (int j = 0; j < i + 1; j++) {
            printf("#");
        }
        /* print the two spaces between the hashes, fixed */
        printf("  "); 
        
        /* print hashes again; same as above */
        for (int j = 0; j < i + 1; j++) {
            printf("#");
        }
        /* move to the next line, no need for extra spaces */
        printf("\n"); 
    }
}
