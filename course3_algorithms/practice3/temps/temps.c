/**
 * @file temps.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief Sorting the data set.
 *          On hindsight, the sorting is in ascending order but it should be in descending.
 *          Not worth it to change it.
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */


// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

enum Select
{
    BUBBLESORT,
    SELECTIONSORT,
    INSERTIONSORT
};

void sort_cities(int selection);
void bubblesort();
void selectionsort();
void insertionsort();

int main(void)
{
    /* the dataset : */

    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    /* SELECT SORTING ALGORITHM HERE */
    sort_cities(INSERTIONSORT);

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

/**
 * @brief Sort cities by temperature in descending order
 */
void sort_cities(int selection)
{
    switch (selection)
    {
    case BUBBLESORT:
        bubblesort();
        break;

    case SELECTIONSORT:
        selectionsort();
        break;
    
    case INSERTIONSORT:
        insertionsort();
        break;

    default:
        printf("something has gone wrong\n");
        break;
    }
}

/**
 * @brief implementation of Bubblesort algorithm
 */
void bubblesort()
{
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        bool swapped = 0;
        /* nested loop makes it O(n²) */
        for (int j = 0; j < NUM_CITIES - i - 1; j++)
        {
            if (temps[j].temp > temps[j + 1].temp)
            {
                /* Swap temps[j] and temps[j + 1] */
                avg_temp temp = temps[j];
                temps[j] = temps[j + 1];
                temps[j + 1] = temp;
                swapped = 1;
            }
        }
        /* If no two elements were swapped by inner loop, then break */
        if (!swapped)
        {
            break;
        }
    }
}

/**
 * @brief implementation of Selection Sort algorithm
 */
void selectionsort()
{
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        /* get the minimum and make sure it's in the lower position*/
        int min_idx = i;
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            if (temps[j].temp < temps[min_idx].temp)
            {
                min_idx = j;
            }
        }
        /* Swap temps[min_idx] and temps[i] */
        avg_temp temp = temps[min_idx];
        temps[min_idx] = temps[i];
        temps[i] = temp;
    }
}

/**
 * @brief implementation of Insertion Sort algorithm
 */
void insertionsort()
{
    for (int i = 1; i < NUM_CITIES; i++)
    {
        avg_temp key = temps[i];
        int j = i - 1;
        /* insert the item in the correct position in the sorted path */
        while (j >= 0 && temps[j].temp > key.temp)
        {
            temps[j + 1] = temps[j];
            j--;
        }
        temps[j + 1] = key;
    }
}