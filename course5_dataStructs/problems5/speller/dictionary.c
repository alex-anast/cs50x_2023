/************************************************************
 * @file dictionary.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief Implements a dictionary's functionality
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************/

/* <> for searching thorugh the standard C libs first */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>      // fopen, fclose
#include <stdlib.h>     // read
#include <string.h>
#include <aio.h>        // ssize_t

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

node *create_node();
bool hash_table_init();

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
    printf("1");
    /* initialize hash table */
    if(!hash_table_init())
    {
        printf("Error initializing hash table\n");
        return false;
    }
    printf("2");

    /* open the file */
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error allocating memory while trying to open dictionary. Exiting\n");
        return false;
    }

    /* initialize necessary values */
    char line[LENGTH + 1];

    do
    {
        /* read each line from the file and handle errors */
        if (fgets(line, LENGTH, file) == NULL) // puts a NUL char at the end of the string
        {
            /* indicate error */
            printf("End of reading from dictionary.\n");
            /* per the man page, even if it fails, the freeing is mandatory */
            break;
        }

        /* remove the trailing newline character, if present */
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n')
        {
            line[line_len - 1] = '\0';
        }

        /* create the node */
        node *node_word = create_node();
        /* error handling */
        if (node_word == NULL)
        {
            printf("Could not create node.\n");
            return false;
        }

        /* copy the dictionary word into the node */
        char *status = strcpy(node_word->word, line);
        /* error handling */
        if (status == NULL)
        {
            printf("Failed to copy string.\n");
            return false;
        }

        /* compute the hash value */
        int hash_value = hash(node_word->word);
        
        /* insert the word into the hash table */
        // TODO : hash_table_insert(node *new_node);
        /* if it is the first element into the hash bucket */
        if (table[hash_value] == NULL)
        {
            table[hash_value] = node_word;
        }
        /* else, if there is already a node in the hash bucket */
        else
        {
            /* set "cursor" */
            node *current_node = table[hash_value];
            /* when I reach the end */
            while (current_node->next != NULL)  // TODO : insertion could be done on the first position for speed
            {
                current_node = current_node->next;
            }
            /* update the singly-linked list by appending the new node at the end */
            current_node->next = node_word;
        }
    } while (1);

    /* close the file */
    fclose(file);
    
    /* return success */
    return true;
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

node *create_node()
{
    /* allocate memory for node */
    node *new_node = (node *)malloc(sizeof(node));
    /* error handling */
    if (new_node == NULL)
    {
        printf("Failed to allocate node.\n");
        return NULL;
    }
    return new_node;
}

bool hash_table_init()
{
    /* for every hash bucket */
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        /* allocate necessary memory */
        table[i] = (node *)malloc(sizeof(node));
        /* error handling */
        if (table[i] == NULL)
        {
            printf("Error allocating memory while init\n");
            return false;
        }

        /* initialize hash bucket's first node */
        table[i]->next = NULL;
        if (strcpy(table[i]->word, "") == NULL)
        {
            printf("Error copying string while init\n");
            return false;
        }
    }
    return true;
}