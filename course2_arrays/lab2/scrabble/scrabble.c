/**
 * @file scrabble.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com    )
 * @brief scrabble game - lab 2 of CS50x Harvard 2023
 * @version 0.1
 * @date 2023-04-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* Points assigned to each letter of the alphabet from Scrabble game rules */
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("ERROR!\n");
    }

    return 0;
}

/**
 * @brief computes the Scrabble score based on the given word referring to a global POINTS array
 * 
 * @param word 
 * @return int 
 */
int compute_score(string word)
{
    // TODO: Compute and return score for string

    /* define score variable to keep the final score and init to 0 as starting point */
    int total_score = 0;

    /* for every character in the word */
    for (int i = 0, word_length = strlen(word); i < word_length; i++)
    {
        /* how many points does the character score? add the points to the total_score variable */
        /* if the character is a proper letter */
        if (isalpha(word[i]))
        {
            /* use lowercase and subtract from the ASCII 'a' to properly index the POINTS array */
            total_score += POINTS[tolower(word[i]) - 'a'];
        }
    }

    /* return the score */
    return total_score;
}
