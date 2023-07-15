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
#include <stdlib.h>
#include <string.h>
#include <strings.h>    // strcasecmp

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

node *node_create();
bool hash_table_init();
void hash_table_insert(int hash_value, node *new_node);
void node_destroy(int index);
bool node_lookup(const char *word, node *root);

// TODO: Choose number of buckets in hash table
#define HASH_TABLE_SIZE 1000

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
    /* get hash value */
    int hash_value = hash(word);
    /* perform lookup in the singly-linked list and return true/false */
    return node_lookup(word, table[hash_value]);
}

/**
 * @brief Hashes word to a number
 * 
 * @param word 
 * @return unsigned int 
 */
unsigned int hash(const char *word)
{   
    /**
     * sample text: lalaland.txt (found in repo)
     * let's set HASH_TABLE_SIZE = 1000 as a maximum allowed value from my memory.
     * 
     * use of prime number to ensure that the multiplications are "weird".
     * for every character, I am assigning a weight based on its location in the word.
     * 
     * In general, I tried to include as many parameters as possible in order to
     * make every word different than the rest.
     */

    /* define prime. Has to be small because of overflow */
    unsigned int prime = 31;
    unsigned long long hash_value = 0;
    /* repeat the process for every character in the word */
    for (int i = 0, word_length = strlen(word); i < word_length; i++)
    {
        /* using ascii for retrieving int */
        int int_from_ascii = toupper(word[i]) - 'A';
        /* then a sum will be greated, diversifying the words */
        hash_value += int_from_ascii * prime * i;
    }
    return hash_value % HASH_TABLE_SIZE;
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
    /* initialize hash table */
    if (!hash_table_init())
    {
        printf("Error initializing hash table\n");
        return false;
    }

    /* open the file */
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error allocating memory while trying to open dictionary. Exiting\n");
        return false;
    }

    /* initialize necessary values */
    char line[LENGTH + 2]; // +1 for \n and +1 for \0 that fgets puts

    /* read each line from the file */
    while (fgets(line, LENGTH + 2, file)) // +1 for the \n character and +1 because it needs it internally
    {
        /* remove the trailing newline character, if present */
        unsigned int line_len = strlen(line);
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n')
        {
            /* and replace it with NUL */
            line[line_len - 1] = '\0';
        }

        /* create the node */
        node *node_word = node_create();
        /* error handling */
        if (node_word == NULL)
        {
            printf("Could not create node.\n");
            return false;
        }

        /* copy the dictionary word into the node */
        /* use of strncpy to ensure correct copy size. Does not necessarily include NUL */
        char *status = strncpy(node_word->word, line, LENGTH);
        /* error handling */
        if (status == NULL)
        {
            printf("Failed to copy string.\n");
            return false;
        }
        /* even if not needed, make sure of NUL character in the end */
        node_word->word[LENGTH] = '\0';

        /* compute the hash value */
        int hash_value = hash(node_word->word);

        /* insert the word into the hash table */
        hash_table_insert(hash_value, node_word);
    }

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
    /* initialize counter */
    unsigned int count = 0;
    /* for every hash bucket */
    for (int ht_index = 0; ht_index < HASH_TABLE_SIZE; ht_index++)
    {
        /* get the node from the hash table */
        node *cursor_node = table[ht_index];
        /* traverse through the sll */
        while (cursor_node != NULL)
        {
            /* if it contains a valid word */
            if (strcmp(cursor_node->word, "") != 0)
            {
                /* count the node */
                count++;
            }
            /* update cursor - it will be NULL if not pointing anywhere and the loop will stop */
            cursor_node = cursor_node->next;
        }
    }
    return count;
}

/**
 * @brief Unloads dictionary from memory, returning true if successful, else false
 * 
 * @return true 
 * @return false 
 */
bool unload(void)
{
    /* for every hash bucket */
    for (int ht_id = 0; ht_id < HASH_TABLE_SIZE; ht_id++)
    {
        node_destroy(ht_id);
    }
    return true;
}

/**
 * @brief Create a node object for the hash table and return it
 * 
 * @return node* 
 */
node *node_create()
{
    /* allocate memory for node */
    node *new_node = (node *)malloc(sizeof(node));
    /* error handling */
    if (new_node == NULL)
    {
        printf("Failed to allocate node.\n");
        return NULL;
    }
    /* initialize singly-linked list node */
    new_node->next = NULL;
    char *success = strcpy(new_node->word, "");
    if (success == NULL)
    {
        printf("Error initializing the node word\n");
        return NULL;
    }

    return new_node;
}

/**
 * @brief initialize hash table
 * 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Implement the insertion in a hash table
 * 
 * @param hash_value 
 * @param new_node 
 */
void hash_table_insert(int hash_value, node *new_node)
{
    /* if it is the first element into the hash bucket */
    if (table[hash_value] == NULL)
    {
        table[hash_value] = new_node;
    }
    /* else, if there is already a node in the hash bucket */
    else
    {
        /* set "cursor" */
        node *cursor = table[hash_value];
        /* set the new node at the start of the sll */
        table[hash_value] = new_node;
        /* put the ssl in the continuation of the new node */
        table[hash_value]->next = cursor;
    }
}

/**
 * @brief destroy the node from an ssl from the front
 * 
 * @param index 
 */
void node_destroy(int index)
{
    /* set pointers */
    node *current_node = table[index];
    node *cursor = NULL;
    /* destroy from the front of the sll */
    while (current_node != NULL)
    {
        /* get the pointer to the next node of the hash bucket */
        cursor = current_node->next;
        /* free current node */
        free(current_node);
        /* if cursor points at something, then loop will repeat */
        current_node = cursor;
    }
}

/**
 * @brief traverse a singly-linked list return if the word has been found
 * 
 * @param word 
 * @param root 
 * @return true 
 * @return false 
 */
bool node_lookup(const char *word, node *root)
{
    bool found = false;
    /* traverse the linked list until there is nothing left to point */
    while (root != NULL)
    {
        /* if the words match, without caring about capital letters etc */
        if (strcasecmp(root->word, word) == 0)
        {
            /* found ! */
            return true;
        }
        /* after checking, proceed to the next node */
        root = root->next;
    }
    /* if exited the loop, then it has not been found */
    return false;
}

