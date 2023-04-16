/**
 * @file wordle.c
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief Wordle50 game from CS50x Harvard 2023. I want to experiment with test-oriented software
 * @version 0.1
 * @date 2023-04-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>

/* each of our text files contains 1000 words */
#define LISTSIZE 1000

/* values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter) */
#define EXACT 2
#define CLOSE 1
#define WRONG 0

/* ANSI color codes for boxed in letters */
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

/* user-defined function prototypes */
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    /* ensure proper usage - check if at least one argument and if it is a number too */
    assert(argc == 2 && "Usage: ./wordle wordsize");

    /* check if the input string contains only a single digit */
    assert(isdigit(argv[1][0]) && "Input is not an integer!");

    /* convert input to integer */
    int wordsize = atoi(argv[1]);

    /* ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead */
    assert((wordsize >= 5 && wordsize <= 8) && "Error: wordsize must be either 5, 6, 7, or 8\n");

    /* open correct file, each file has exactly LISTSIZE words */
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    assert(wordlist != NULL && "Error opening file");

    /* load word file into an array of size LISTSIZE */
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        assert(fscanf(wordlist, "%s", options[i]) == 1 && "Error reading file");
    }

    /* pseudorandomly select a word for this game */
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    /* allow one more guess than the length of the word */
    int guesses = wordsize + 1;
    int won = 0;

    /* print greeting, using ANSI color codes to demonstrate */
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    /* main game loop, one iteration for each guess */
    for (int i = 0; i < guesses; i++)
    {
        /* obtain user's guess */
        string guess = get_guess(wordsize);

        /* array to hold guess status, initially set to zero */
        int status[wordsize];

        /* set all elements of status array initially to 0, aka WRONG */
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        /* Calculate score for the guess */
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);
        
        /* Print the guess */
        print_word(guess, wordsize, status);

        /* if they guessed it exactly right, set terminate loop */
        if (score == EXACT * wordsize)
        {
            won = 1;
            break;
        }
    }

    /* Print the game's result */
    if (won)
    {
        printf("You won!\n");
    }

    /* that's all folks! */
    fclose(wordlist);
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";

    /* ensure users actually provide a guess that is the correct length */
    do
    {
        guess = get_string("Input a %d-letter word: ", wordsize);
    }
    while (strlen(guess) != wordsize);
    
    return guess;
}

/**
 * @brief compare guess to choice and score points as appropriate, storing points in status
 * 
 * @param guess user input
 * @param wordsize string length of guess
 * @param status comes from enum, it's the identification of whether the letter is wrong or not etc.
 * @param choice the end-goal word
 * @return int 
 */
int check_word(string guess, int wordsize, int status[], string choice)
{
    assert(guess != NULL && "Guess string cannot be NULL.");
    assert(status != NULL && "Status array cannot be NULL.");
    assert(choice != NULL && "Choice string cannot be NULL.");

    int score = 0;

    /* iterate over each letter of the guess */
    for (int i = 0, guess_length = strlen(guess); i < guess_length; i++)
    {
        /* iterate over each letter of the choice */
        for (int j = 0, choice_length = strlen(choice); j < choice_length; j++)
        {
            /* compare the current guess letter to the current choice letter */
            if (guess[i] == choice[j])
            {
                /* if they're the same position in the word */
                if (i == j)
                {
                    /* then score EXACT points (green) */
                    status[i] = EXACT;
                    /* break so you don't compare that letter further */
                    break;
                }
                /* it's in the word, but not the right spot */
                else
                {
                    /* then score CLOSE point (yellow) */
                    status[i] = CLOSE;
                }
            }
        }
        assert(status[i] == EXACT || status[i] == CLOSE || status[i] == WRONG && "Invalid status value.");

        /* keep track of the total score by adding each individual letter's score from above */
        score += status[i];
    }

    return score;
}

/**
 * @brief print word character-for-character with correct color coding, then reset terminal font to normal
 * 
 * @param guess 
 * @param wordsize 
 * @param status 
 */
void print_word(string guess, int wordsize, int status[])
{

    /* for the coloring of every character respectively */
    for (int i = 0; i < wordsize; i++)
    {
        assert(status[i] == EXACT || status[i] == CLOSE || status[i] == WRONG && "Invalid status");
        switch (status[i])
        {
        case EXACT:
            printf(GREEN"%c"RESET, guess[i]);
            break;
        
        case CLOSE:
            printf(YELLOW"%c"RESET, guess[i]);
            break;

        default: /* WRONG */
            printf(RED"%c"RESET, guess[i]);
            break;
        }
    }

    printf("\n");
    return;
}
