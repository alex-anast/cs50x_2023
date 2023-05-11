/**
 * @brief Saves popular dog names in a trie
 *        https://www.dailypaws.com/dogs-puppies/dog-names/common-dog-names
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ALPHABET    26
#define MAXCHAR             20

typedef struct node
{
    int is_word;
    /* how a trie is defined: as an array of pointers */
    struct node *children[SIZE_OF_ALPHABET];
}
/* notice that it's possible to repeat the name, it's not confusing the compiler */
node;

/* function prototypes */
int check(char *word);
int unload(void);
void unloader(node *current);

/* root of trie */
node *root;

/* buffer to read dog names into */
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    /* check for command line args */
    if (argc != 2)
    {
        printf("Usage: ./trie infile\n");
        return 1;
    }

    /* file with names */
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return 1;
    }

    /* allocate root of trie */
    root = malloc(sizeof(node));
    /* error handling if memory is maxed out */
    if (root == NULL)
    {
        return 1;
    }

    /* initialize root */
    root->is_word = 0;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        root->children[i] = NULL;
    }

    /* add words to the trie */
    while (fscanf(infile, "%s", name) == 1) 
    {
        /* set the cursor to root */
        node *cursor = root;

        /* for each character in the name */
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            /* obtain index relative to ASCII table */
            int index = tolower(name[i]) - 'a';
            /* if next node does not exist */
            if (cursor->children[index] == NULL)
            {

                /* make node */
                node *new = malloc(sizeof(node));
                new->is_word = 0;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    new->children[j] = NULL;
                }
                cursor->children[index] = new;
            }

            /* go to node which has just been made */
            cursor = cursor->children[index];
        }

        /* if end of the word, mark it as being a word */
        cursor->is_word = 1;
    }

    /* lookup */
    if (check(get_string("Check word: ")))
    {
        printf("Found!\n");
    }
    else
    {
        printf("Not Found.\n");
    }

    if (!unload())
    {
        printf("Problem freeing memory!\n");
        return 1;
    }

    fclose(infile);
}

/**
 * @brief lookup throught the trie and return 1 if found or 0 if not found
 * 
 * @param word 
 * @return int 
 */
int check(char* word)
{
    /* cursor to iterate through the trie */
    node *cursor = root;

    /* for all the letters in the word */
    for (int letter = 0, string_size = strlen(word); letter < string_size; letter++)
    {
        /* obtain index relative to ASCII table */
        int index = tolower(word[letter]) - 'a';
        /* go to that index and check if it exists */
        if (cursor->children[index] == NULL)
        {
            /* trie has reached the end, no such word found */
            return 0;
        }
        /* update cursor */
        cursor = cursor->children[index];
    }
    /* have traversed through all the word, return found */
    return 1;
}

/**
 * @brief unload trie from memory
 * 
 * @return int 
 */
int unload(void)
{
    /* the recursive function handles all of the freeing */
    unloader(root);
    return 1;
}

/**
 * @brief free the memory
 * 
 * @param current 
 */
void unloader(node* current)
{
    /* iterate over all the children to see if they point to anything and go there if they do point */
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
        {
            /* that way it targets (and frees) all existing nodes */
            unloader(current->children[i]);
        }
    }

    /* after we check all the children point to null we can get rid of the node and return to the previous iteration of this function. */
    free(current);
}
