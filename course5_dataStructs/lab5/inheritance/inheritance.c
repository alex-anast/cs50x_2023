/*******************************************************************
 * @file inheritance.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief Simulate genetic inheritance of blood type
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 ********************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PARENTS_NO 2

/* each person has two parents and two alleles */
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();
char random_allele_from_parents(person *parent);

int main(void)
{
    /* seed random number generator */
    srand(time(0));

    /* create a new family with three generations */
    person *p = create_family(GENERATIONS);
    if (p == NULL)
    {
        fprintf(stderr, "Error in creating a family, exiting.\n");
        return 1;
    }

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
    /* allocate memory for new person */
    person *new_person = (person *)malloc(sizeof(person));
    if (new_person == NULL)
    {
        fprintf(stderr, "Allocation error.\n");
        return NULL;
    }

    /* if there are still generations left to create */
    if (generations > 1)
    {
        /* create two new parents for current person by recursively calling create_family */
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        /* set parent pointers for current person */
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        /* randomly assign current person's alleles based on the alleles of their parents */
        new_person->alleles[0] = random_allele_from_parents(parent0);
        new_person->alleles[1] = random_allele_from_parents(parent1);
    }

    /* if there are no generations left to create */
    else
    {
        /* set parent pointers to NULL */
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        /* randomly assign alleles of the root */
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    /* return newly created person */
    return new_person;
}

/**
 * @brief free `p` and all ancestors of `p`
 *        assuming that it will always have two parents
 * 
 * @param p 
 */
void free_family(person *p)
{
    /* handle base case */
    if (p) // root
    {
        /* free parents recursively */
        if (p->parents[0] != NULL)
        {
            free_family(p->parents[0]);
        }
        if (p->parents[1] != NULL)
        {
            free_family(p->parents[1]);
        }
        /* free child */
        free(p);
    }
}

/**
 * @brief Print each family member and their alleles.
 * 
 * @param p 
 * @param generation 
 */
void print_family(person *p, int generation)
{
    /* handle base case */
    if (p == NULL)
    {
        return;
    }

    /* print indentation */
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    /* print person */
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

    /* print parents of current generation */
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

/**
 * @brief from the two characters that the parent has, randomly pick one
 * 
 * @param parent 
 * @return char 
 */
char random_allele_from_parents(person *parent)
{
    /* rand() returns int between 0 and RAND_MAX == at least 32767 (varies, stdlib.h) */
    int r = rand() % 2;
    if (r == 0)
    {
        return parent->alleles[0];
    }
    else
    {
        return parent->alleles[1];
    }
}