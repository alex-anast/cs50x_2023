#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_words(const string text);
int count_letters(const string text);
int count_sentences(const string text);
int in_array(char c, string arr);
float letters_per_words_average(const int letters, const int words);
float sentences_per_words_average(const int sentences, const int words);
int coleman_liau_index(const string text);

int main(void) 
{
    string text = get_string("What is the text? ");

    /* calculate Grade X*/
    int grade = coleman_liau_index(text);

    printf("words     = %d\n", count_words(text));
    printf("letters   = %d\n", count_letters(text));
    printf("sentences = %d\n", count_sentences(text));

    /* Specifications output */
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}

/**
 * @brief count the words of a string
 * 
 * @attention any sequence of characters separated by spaces should count as a word
 * 
 * @param text 
 * @return int 
 */
int count_words(const string text)
{
    /* count the words variable */
    int count = 0;
    
    /* true - false, if character belongs to human-defined word or not */
    int in_word = 0;

    /* loop through the string */
    for (int i = 0; text[i] != '\0'; i++)
    {
        /* assume that the word ends on spaces */
        if (isspace(text[i]))
        {
            /* if in word, this is the end of it */
            if (in_word)
            {
                count++;
                in_word = 0;
            }
        }
        else
        {
            /* this character is part of a word */
            in_word = 1;
        }
    }
    /* if in word at the end of the string, count it */
    if (in_word)
    {
        count++;
    }

    return count;
}

/**
 * @brief count the letters of a string
 * 
 * @attention a letter is any lowercase character from a to z or any uppercase character from A to Z
 * 
 * @param text 
 * @return int 
 */
int count_letters(const string text)
{
    /* count letters variable */
    int count = 0;
    
    /* Iterate through each character in the string */
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        /* Check if the character is an alphabet letter */
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    
    return count;
}

/**
 * @brief helper function to check if a character is in an array
 * 
 * @param c 
 * @param arr 
 * @return int 
 */
int in_array(char c, string arr)
{
    /* loop through the punctuation chars */
    for (int i = 0, arr_length = strlen(arr); i < arr_length; i++)
    {
        if (c == arr[i])
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief counte the sentences of a string
 * 
 * @attention any occurrence of a period, exclamation point, or question mark indicates the end of a sentence
 * 
 * @param text 
 * @return int 
 */
int count_sentences(const string text)
{
    /* count sentences variable */
    int count = 0;

    /* true - false, if character belongs to human-defined word or not */
    int in_sentence = 0;

    /* symbols indicating end of a sentence - ispunct() creates probem with commas etc */
    string sentence_endings = ".?!";

    /* loop through the string */
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        /* assume that the sentence ends on punctiation points */
        if (in_array(text[i], sentence_endings))
        {
            /* if previously in sentence, then now it's out of sentence, so count 1 more */
            if (in_sentence)
            {
                count++;
                in_sentence = 0;
            }
        }
        else
        {
            /* this character is part of the sentence */
            in_sentence = 1;
        }
    }
    return count;
}

/**
 * @brief find average number of LETTERS per 100 words in the text
 * 
 * @param text 
 * @return int 
 */
float letters_per_words_average(const int letters, const int words)
{
    return letters / (float) words;
}

/**
 * @brief find average number of SENTENCES per 100 words in the text
 * 
 * @param text 
 * @return int 
 */
float sentences_per_words_average(const int sentences, const int words)
{
    return sentences / (float) words;
}

/**
 * @brief The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text.
 * 
 * @param text 
 * @return int 
 */
int coleman_liau_index(const string text)
{
    /* caluclate once to avoid overhead */
    int words = count_words(text);

    /* average number of letters per 100 words in text */
    float L = letters_per_words_average(count_letters(text), words) * 100;

    /* average number of sentences per 100 words in text */
    float S = sentences_per_words_average(count_sentences(text), words) * 100;

    /* rounded to the nearest integer */
    return round(0.0588 * L - 0.296 * S - 15.8);
}
