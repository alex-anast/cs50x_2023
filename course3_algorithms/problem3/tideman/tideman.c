/**
 * @file tideman.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief Tideman voting algorithm
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 * Steps:
 *  Tally:  Once all of the voters have indicated all of their preferences, determine, for each pair of candidates,
 *          who the preferred candidate is and by what margin they are preferred.
 *  Sort:   Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory
 *          is defined to be the number of voters who prefer the preferred candidate.
 *  Lock:   Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair
 *          to the candidate graph, so long as locking in that pair does not create a cycle in the graph.
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
int locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
/* the pairs are all the possible combinations */
pair pairs[MAX * (MAX - 1) / 2];

/* globals */
int pair_count;
int candidate_count;

// Function prototypes
int vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(int left, int right);
int has_cycle(int v, int visited[], int stack[], int adj_matrix[][candidate_count]);
int find_source_id();

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2; // custom error codes
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    /* initialize the preferences 2D array */
    memset(preferences, 0, sizeof(preferences));

    /* for all the voters */
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        /* for each vote */
        for (int j = 0; j < candidate_count; j++)
        {
            /* get the name for the rank i */
            string name = get_string("Rank %i: ", j + 1);

            /* if it is not a valid vote */
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        /* record the ranks */
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

/**
 * @brief Update ranks given a new vote
 *          Assume that no two candidates will have the same name
 * 
 * @param rank the voter's rank'th preference -> it's an index on ranks[]
 * @param name the candidate's name
 * @param ranks[] keeps in ith position the candidate index
 * @return int true or false condition for whether the name of the votee was found
 */
int vote(int rank, string name, int ranks[])
{
    /* from all the candidates */
    for (int i = 0; i < candidate_count; i++)
    {
        /* If name is a match for the name of a valid candidate */
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return 1;
        }
    }

    /* return false in case of error or not found */
    return 0;
}

/**
 * @brief Update preferences array given one voter's ranks to add the current preference
 *          Called once for each voter.
 *          preferences[i][j] should represent the number of voters who prefer candidate i over candidate j.
 *          You may assume that every voter will rank each of the candidates.
 * 
 * @param ranks[] keeps in ith position the candidate index
 */
void record_preferences(int ranks[])
{
    /* set up the indexes */
    int examined_rank = 0, next_ones_i = 0;
    int candidate_index_examined, candidate_index_next;
    /* while the examined rank is not the last one */
    while (examined_rank != candidate_count - 1)
    {
        /* find candidate index in the examined rank */
        candidate_index_examined = ranks[examined_rank];
        /* for all the next ones */
        for (next_ones_i = examined_rank + 1; next_ones_i < candidate_count; next_ones_i++)
        {
            /* find candidate index in the next rank */
            candidate_index_next     = ranks[next_ones_i];
            /* record the preference on these indexes */
            preferences[candidate_index_examined][candidate_index_next]++;
        }
        examined_rank++;
    }
}

/**
 * @brief Record pairs of candidates where one is preferred over the other
 *          update the global variable pair_count
 *          pairs all stored between pairs[0] and pairs[pair_count - 1], inclusive
 */
void add_pairs(void)
{
    /* for all the possible pairs */
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            /* assuming that I will never exceed the maximum allowed pairs amount */
            // if (pair_count < MAX_PAIRS) { ... }

            /* if i is more preferred than j */
            if (preferences[i][j] > preferences[j][i])
            {
                /* add the pair*/
                pairs[pair_count].winner = i;
                pairs[pair_count].loser  = j;
                /* update the global variable pair_count to be the number of pairs of candidates */
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser  = i;
                /* as before, updated in every iteration */
                pair_count++;
            }
            /* if the preferences are tied, skip completely */
            else
            {
                /* readability */
                ;
            }
        }
    }
}

/**
 * @brief Merge sort implementation for sorting pairs in decreasing order by strength of victory
 */
void merge_sort(int left, int right)
{
    /* base case */
    if (left >= right)
    {
        return;
    }

    /* recursive case */
    int mid = left + (right - left) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);

    /* merge */
    int i = left;
    int j = mid + 1;
    int k = 0;
    pair temp[right - left + 1];
    while (i <= mid && j <= right)
    {
        int pref_i_j = preferences[pairs[i].winner][pairs[i].loser];
        int pref_j_i = preferences[pairs[j].winner][pairs[j].loser];
        if (pref_i_j > pref_j_i)
        {
            temp[k++] = pairs[i++];
        }
        else if (pref_i_j < pref_j_i)
        {
            temp[k++] = pairs[j++];
        }
        else
        {
            /* if tie, just use the order in which they appear in the original pairs array */
            temp[k++] = pairs[i++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = pairs[i++];
    }
    while (j <= right)
    {
        temp[k++] = pairs[j++];
    }
    for (int l = 0; l < k; l++)
    {
        pairs[left + l] = temp[l];
    }
}

/**
 * @brief Sort pairs in decreasing order by strength of victory
 *          where strength of victory is defined to be the number of voters who prefer the preferred candidate
 */
void sort_pairs(void)
{
    /* call mergesort - customized for strength of victory measure */
    merge_sort(0, pair_count - 1);
}

/**
 * @brief Lock pairs into the candidate graph in order, without creating cycles
 * 
 */
void lock_pairs(void)
{
    /* Loop through the pairs in decreasing order of victory strength */
    for (int i = 0; i < pair_count; i++)
    {
        /* get the id of the winner and the loser */
        int winner_id = pairs[i].winner;
        int loser_id = pairs[i].loser;

        /* Check if adding the pair will create a cycle : */

        /* define adjacent matrix */
        int adj_matrix[candidate_count][candidate_count];

        /* clone the locked array to the adjacent_matrix array to put under test */
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                adj_matrix[j][k] = locked[j][k];
            }
        }

        /* put the adjacent matric under test : */

        /* supposedly we create the edge */
        adj_matrix[winner_id][loser_id] = 1;

        /* allocate memory for visited and stack arrays in the heap for more memory */
        int *visited = (int *) calloc(candidate_count, sizeof(int));
        int *stack = (int *) calloc(candidate_count, sizeof(int));

        /* if the cloned graph passes the test */
        if (!has_cycle(winner_id, visited, stack, adj_matrix))
        {
            /* then add the edge to the real graph */
            locked[winner_id][loser_id] = 1;
        }

        /* important to free the memory from the heap (checked valgrind) */
        free(visited);
        free(stack);
    }
}

/**
 * @brief uses Depth First Search Traversal to figure out if a cycle exists or not
 * 
 * @param v 
 * @param visited 
 * @param stack 
 * @param adj_matrix 
 * @return int true or false whether the graph has a cycle or not 
 */
int has_cycle(int v, int visited[], int stack[], int adj_matrix[][candidate_count])
{
    /* since visited, set as true */
    visited[v] = 1;
    stack[v] = 1;
    /* for all the nodes */
    for (int i = 0; i < candidate_count; i++)
    {
        /* if exists and not visited */
        if (adj_matrix[v][i] && !visited[i])
        {
            /* recursively call the DFS */
            if (has_cycle(i, visited, stack, adj_matrix))
            {
                /* cycle has been found already, return false until full exit */
                return 1;
            }
        }
        /* if visited and exists in stack */
        else if (adj_matrix[v][i] && stack[i])
        {
            /* then there is a cycle */
            return 1;
        }
    }
    /* if reached this point, there is no cycle */
    stack[v] = 0;
    return 0;
}

/**
 * @brief checks if candidate is the source == does not have any incoming edges
 * 
 * @param candidate 
 * @return int 
 */
int find_source_id()
{
    /* flag for condition */
    int found_winner;

    /* check if the candidate has any incoming edges */
    for (int i = 0; i < candidate_count; i++)
    {
        /* assume inocent before guilty */
        found_winner = 1;

        for (int j = 0; j < candidate_count; j++)
        {
            /* if there is an incoming edge */
            if (locked[j][i])
            {
                /* it is NOT a source - proceed to the next one */
                found_winner = 0;
                break;
            }
        }

        /* if there is no incoming edge */
        if (found_winner)
        {
            /* return the index of the winning candidate */
            return i;
        }
    }
    /* there is no way a winner will not be found */
    return -1;
}

/**
 * @brief Print the winner of the election
 * 
 */
void print_winner(void)
{
    /* assume there will not be more than one source */
    int winner_id = find_source_id();
    printf("%s\n", candidates[winner_id]);
}
