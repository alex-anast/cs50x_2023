/**
 * @file population.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief   
 *          
 *          
 *          
 *          
 * @version 0.1
 * @date 2023-04-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <cs50.h>
#include <stdio.h>

/**
 * @brief n llamas -> per year, n / 3 new llamas and n / 4 llamas pass away
 *        if n = 1200 llamas, then 
 *            if (year +1), 1200 / 3 = 400 new and 1200 / 4 = 300 llamas pass away
 *        year +1 -> 1200 + 400 - 300 = 1300 llamas.
 *        if n = 1000 llamas, 1000 / 3 = 333.33 new -> 333 new, 1000 / 4 = 250 pass away, total 1083
 * 
 * @param start 
 * @param end 
 * @return int
 */
int calculate_years(int start, int end)
{
    int population = start;

    int years = 0;

    do
    {
        population += (population / 3) - (population / 4);
        years++;
    }
    while (population < end);

    return years;
}

int main(void)
{
    /* Prompt for start size */
    int population_start;
    
    do
    {
        population_start = get_int("Llamas at the start? ");
    }
    while (population_start < 9);

    /* Prompt for end size */
    int population_end;
    
    do
    {
        population_end = get_int("At how many llamas do we stop? ");
    }
    while (population_end < population_start);

    /* Calculate number of years until we reach threshold */
    int years = calculate_years(population_start, population_end);

    /* Print number of years */
    printf("Years: %d\n", years);

    return 0;
}
