/**
 * @file dictionary.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief Implements a dictionary's functionality
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/* <> for searching thorugh the standard C libs first */
#include <ctype.h>
#include <stdbool.h>

/* "" for searching through the current directory first */
#include "dictionary.h"

/* represents a node in a hash table */
typedef struct node
{
    /* +1 for the NUL */
    char word[LENGTH + 1];
    /* implements a singly-linked list */
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
#define HASH_TABLE_SIZE 26

/* hash table */
node *table[HASH_TABLE_SIZE];

/**
 * @brief Returns true if word is in dictionary, else false
 * 
 * @param word 
 * @return true 
 * @return false 
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * @brief Hashes word to a number
 * 
 * @param word 
 * @return unsigned int 
 */
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

/**
 * @brief Loads dictionary into memory, returning true if successful, else false
 * 
 * @param dictionary 
 * @return true 
 * @return false 
 */
bool load(const char *dictionary)
{
    // TODO
    return false;
}

/**
 * @brief Returns number of words in dictionary if loaded, else 0 if not yet loaded
 * 
 * @return unsigned int 
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * @brief Unloads dictionary from memory, returning true if successful, else false
 * 
 * @return true 
 * @return false 
 */
bool unload(void)
{
    // TODO
    return false;
}
