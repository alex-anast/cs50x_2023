#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX_CANDIDATES 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Number of candidates
int candidate_count;

// Function prototypes
int vote(string name);
void print_winner(void);
int find_winners(void);
void sort_candidates(void);
void merge(candidate arr[], int left, int mid, int right);
void mergeSort(candidate arr[], int left, int right);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

/**
 * @brief Update vote totals given a new vote
 * 
 * @param name representing the candidate who was voted for
 * @return int 
 */
int vote(string name)
{
    /* search throught the candidates */
    for (int i = 0; i < candidate_count; i++)
    {
        /* if name matches one of the names of the candidates in the election */
        if (!strcmp(name, candidates[i].name))
        {
            /* update that candidate’s vote total to account for the new vote */
            candidates[i].votes++;
            /* no point in further traversing the candidates -> successful ballot */
            return 1;
        }
    }
    /* name not found - return false */
    return 0;
}

/**
 * @brief Print the winner (or winners) of the election
 */
void print_winner(void)
{
    /* find how many winners there will be */
    int count_winners = find_winners();
    /* for the number of winners, print their names */
    for (int i = 0; i < count_winners; i++)
    {
        /* since the candidates are sorted now, no need for a find function */
        printf("%s\n", candidates[i].name);
    }
}

int find_winners(void)
{
    /* sort the candidates GLOBALLY */
    sort_candidates();

    /* define the necessary variables  */
    int count_winners = 1;
    int winning_value = candidates[0].votes;
    int i = 1;

    /* while the next candidate has the same votes */
    while (candidates[i].votes == winning_value)
    {
        /* add him to the count */
        count_winners++;
        /* never forget again the index of the loop dumbass */
        i++;
    }

    /* return the count winners */
    return count_winners;
}

void sort_candidates(void)
{
    /* doesn´t matter if it's global or not */
    mergeSort(candidates, 0, candidate_count - 1);
}

/**
 * @brief implementation of the merging for Merge Sort
 * 
 * @param arr 
 * @param left 
 * @param mid 
 * @param right 
 */
void merge(candidate arr[], int left, int mid, int right)
{
    int i, j, k;
    /* calculate the two sizes */
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    /* local for merging */
    candidate L[n1], R[n2];
    
    /* once for the left struct */
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    
    /* once for the right struct */
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }
    
    i = 0;
    j = 0;
    k = left;
    
    /* merge depending on the condition */
    while (i < n1 && j < n2)
    {
        /* this condition */
        if (L[i].votes >= R[j].votes)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    /* and finally, put in the proper struct */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Merge Sort algorithm implementation
 * 
 * @param arr 
 * @param left 
 * @param right 
 */
void mergeSort(candidate arr[], int left, int right)
{
    /* run the check */
    if (left < right)
    {
        /* calculate the mid element */
        int mid = left + (right - left) / 2;
        
        /* recursively calls itself with the smaller struct now */
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        /* and merges based on the condition */
        merge(arr, left, mid, right);
    }
}
