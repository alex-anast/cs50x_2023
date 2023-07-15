/**
 * @file dictionary.h
 * @author Alexandros Anastasiou (AnastasioyAA@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* pre-processor macro to not re-compile if reused */
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

/* maximum length for a word */
/* (e.g., pneumonoultramicroscopicsilicovolcanoconiosis) */
#define LENGTH 45

/* prototypes */
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif /* DICTIONARY_H */
