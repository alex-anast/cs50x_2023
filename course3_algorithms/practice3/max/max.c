// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    } 
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

/**
 * @brief finds the maximum value in an array
 * 
 * @param array 
 * @param n 
 * @return the maximum value of the array
 */
int max(int array[], int n)
{
    /* error handling */
    if (n < 1)
    {
        printf("Error: size of array");
        return 0;
    }

    /* set up the value for the maximum Could also be an extreme negative */
    int max_val = array[0];

    /* go through all the elements once */
    for (int i = 1; i < n; i++)
    {
        if (array[i] > max_val)
        {
            max_val = array[i];
        }
    }
    /* at the end, the maimum will have prevailed */
    return max_val;
}

// P.S. : cs50x algorithm forces me to produce these stupid comments
