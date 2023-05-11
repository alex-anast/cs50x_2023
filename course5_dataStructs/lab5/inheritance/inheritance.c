/**
 * @file inheritance.c
 * @author Alexandros Anasrasiou (AnastasioyAA@gmail.com)
 * @brief simulate genetic inheritance of blood type
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* each person has two parents and two alleles */
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

/* global parameters */
const int GENERATIONS   = 3;
const int INDENT_LENGTH = 4;

/* function definitions */
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    /* seed random number generator */
    srand(time(0));

    /* create a new family with three generations */
    person *p = create_family(GENERATIONS);

    /* print family tree of blood types */
    print_family(p, 0);

    /* free memory */
    free_family(p);
}

/**
 * @brief create a new individual with `generations`
 * 
 * @param generations 
 * @return person* 
 */
person *create_family(int generations)
{
    /* TODO: Allocate memory for new person */
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    /* if there are still generations left to create */
    if (generations > 1)
    {
        /* create two new parents for current person by recursively calling create_family */
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        /* set parent pointers for current person */
        p->parents[0] = parent0;
        p->parents[1] = parent1;

        /* randomly assign current person's alleles based on the alleles of their parents */
        // TODO
    }

    /* if there are no generations left to create */
    else
    {
        /* set parent pointers to NULL */
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        /* TODO: randomly assign alleles */
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();

    }

    /* return newly created person */
    return p;
}

/**
 * @brief Free `p` and all ancestors of `p`.
 * 
 * @param p 
 */
void free_family(person *p)
{
    /* handle base case */
    if (p == NULL)
    {
        fprintf(stderr, "Error, NULL pointer.\n")l
        return;
    }

    /* free parents recursively */
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    /* free child */
    free(p);
}

/**
 * @brief print each family member and their alleles.
 * 
 * @param p 
 * @param generation 
 */
void print_family(person *p, int generation)
{
    /* handle base case */
    if (p == NULL)
    {
        fprintf(stderr, "Error, NULL pointer.\n")l
        return;
    }

    /* Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    /* Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    /* Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}


/**
 * @brief randomly chooses a blood type allele 
 * 
 * @return char 
 */
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
