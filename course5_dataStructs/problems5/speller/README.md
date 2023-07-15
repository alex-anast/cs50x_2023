# Speller

This problem implements a program that spell-checks a file, a la the below, using a **hash table**.

```lang-Bash
$ ./speller texts/lalaland.txt
MISSPELLED WORDS

[...]
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT
[...]
Shangri
[...]
fianc
[...]
Sebastian's
[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
```

## Understanding

Theoretically, on input of size n, an algorithm with a running time of n is “asymptotically equivalent,” in terms of O, to an algorithm with a running time of 2n. Indeed, when describing the running time of an algorithm, we typically focus on the dominant (i.e., most impactful) term (i.e., n in this case, since n could be much larger than 2). In the real world, though, the fact of the matter is that 2n feels twice as slow as n.

The challenge is to implement the fastest spell checker we can! By “fastest,” though, we’re talking actual “wall-clock,” not asymptotic, time.

In speller.c, I’ve put together a program that’s designed to spell-check a file after loading a dictionary of words from disk into memory. That dictionary, meanwhile, is implemented in a file called dictionary.c. (It could just be implemented in speller.c, but as programs get more complex, it’s more convenient to break them into multiple files.) The prototypes for the functions therein, meanwhile, are defined not in dictionary.c itself but in dictionary.h instead. That way, both speller.c and dictionary.c can #include the file. The loading part and the checking part are the main focus of this exercise.

### dictionary.h

The file dictionary.h uses best practices for the headers in C, notice the line **DICTIONARY_H**.Those lines just ensure that, even though dictionary.c and speller.c #include this file, the compiler will only compile it once.

The way it works is that the first time the header file is included, the preprocessor checks whether the macro DICTIONARY_H is defined or not. Since it is not defined the first time, the preprocessor includes the entire contents of the header file, and defines the DICTIONARY_H macro using the #define directive.

If the header file is included again in the same program, the preprocessor checks whether the DICTIONARY_H macro is already defined, and since it is, it skips the entire contents of the header file. This prevents the header file from being included multiple times in the same program, which could lead to naming conflicts and other issues.

Another way this can be done, is with **#pragma once**. However, it is important to note that the #pragma once directive is not officially part of the C standard, but is widely supported by major compilers.

Next, and for the first time, I #include a file called stdbool.h. That’s the file in which bool itself is defined. Before I was using 1 and 0 for true or false returns, because during my experience in Embedded Systems professional environmnets, *stdbool.h* library does not exist in C99. But for bigger implementations, it is nice for readability to use it.

The #define is a “preprocessor directive” that defines a “constant” called LENGTH that has a value of 45. It’s a constant in the sense that you can’t (accidentally) change it in your own code. The difference between "const int" is that the "#define" does not allocate any memory. In fact, the compiler will replace any mentions of LENGTH in the code with, literally, 45. In other words, it’s not a variable, just a find-and-replace trick.

Finally, notice the prototypes for five functions: check, hash, load, size, and unload. Notice how three of those take a pointer as an argument, per the *:

```lang-C
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
```

Recall that char * is what we used to call string. So those three prototypes are essentially just:

```lang-C
bool check(const string word);
unsigned int hash(const string word);
bool load(const string dictionary);
```

And const, meanwhile, just says that those strings, when passed in as arguments, must remain constant.

### dictionary.c

Atop the file, a struct called node is defined, that represents a node in a hash table. A global pointer array has also been declared, the hash table, which will be used to keep track of words in the dictionary. The array contains N node pointers, to match with the default hash function as described below. This, depending on the implementation, can be customized to fit the requirements and runtime goals.

Next, load, check, size, and unload are implemented. Hash is also a very important implementation which defines the dictionary size and functionality. These functions were fine tuned in the solution of the problem to make it as fast as possible as per the specification requirements (see below).

### speller.c

The function called getrusage deploys “benchmarking” (i.e., timing the execution of) the implementations of check, load, size, and unload. Also deploys the how to go about passing check, word by word, the contents of some file to be spell-checked. Ultimately, it reports each misspelling in that file along with a bunch of statistics.

Notice, incidentally, that the usage of speller to be:

```lang-Bash
Usage: speller [dictionary] text
```

where dictionary is assumed to be a file containing a *list of lowercase words*, *one per line*, and text is a file to be spell-checked. As the brackets suggest, provision of dictionary is optional; if this argument is omitted, *speller will use dictionaries/large by default*. In other words, running:

```lang-Bash
./speller text
```

will be equivalent to running:

```lang-Bash
./speller dictionaries/large text
```

where *text* is the file for spell-checking. Suffice it to say, the former is easier to type.

Within the default dictionary, there are 143,091 words, all of which must be loaded into memory. Every word in that file appears in lowercase (even, for simplicity, proper nouns and acronyms). From top to bottom, **the file is sorted lexicographically, with only one word per line (each of which ends with \n)**. No word is longer than 45 characters, and no word appears more than once. During development, it was handy to use a dictionary that contains far fewer words for debugging purposes. In dictionaries/small is one such dictionary. To use it, execute

```lang-Bash
./speller dictionaries/small text
```

### texts/

Again for testing purposes, there is a whole bunch of texts, among them the script from La La Land, the text of the Affordable Care Act, three million bytes from Tolstoy, some excerpts from The Federalist Papers and Shakespeare, and more. 

As an example, this is the output from the lalaland.txt:

```lang-Bash
./speller texts/lalaland.txt

MISSPELLED WORDS

[...]
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT
[...]
Shangri
[...]
fianc
[...]
Sebastian's
[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
```

**TIME IN load**    represents the number of seconds that speller spends executing the implementation of load.
**TIME IN check**   represents the number of seconds that speller spends, in total, executing the implementation of check.
**TIME IN size**    represents the number of seconds that speller spends executing the implementation of size.
**TIME IN unload**  represents the number of seconds that speller spends executing the implementation of unload.
**TIME IN TOTAL**   is the sum of those four measurements.

These times may vary somewhat across executions of speller, depending on what else the codespace is doing, even if there is no change in the code.

## Specification

The challenge is to implement, in order, load, hash, size, check, and unload, **as efficiently as possible** using a hash table in such a way that **TIME IN load, TIME IN check, TIME IN size, and TIME IN unload are all minimized**. To be sure, it’s not obvious what it even means to be minimized, inasmuch as these benchmarks will certainly vary as you feed speller different values for dictionary and for text. But therein lies the challenge, if not the fun, of this problem. This problem provides the chance to design. Although it is always welcome to minimize space, the ultimate enemy is time.

1. The implementation of check is case-insensitive. In other words, if foo is in dictionary, then check should return true given any capitalization thereof; none of foo, foO, fOo, fOO, fOO, Foo, FoO, FOo, and FOO are considered misspelled.
2. Capitalization aside, the implementation of check should only return true for words actually in dictionary. Hard-coding of common words (e.g., the) has been avoided. Moreover, the only possessives allowed are those actually in dictionary. In other words, even if foo is in dictionary, check should return false given foo's if foo's is not also in dictionary.
3. Assume that any dictionary passed to the program will be structured alphabetically sorted from top to bottom with one word per line, each of which ends with \n. Also assume that dictionary will contain at least one word, that no word will be longer than LENGTH (a constant defined in dictionary.h) characters, that no word will appear more than once, that each word will contain only lowercase alphabetical characters and possibly apostrophes, and that no word will start with an apostrophe.
4. Assume that check will only be passed words that contain (uppercase or lowercase) alphabetical characters and possibly apostrophes.
5. The spell checker may only take text and, optionally, dictionary as input. Although it is smart to “pre-process” the default dictionary in order to derive an “ideal hash function” for it, that is prohibited.
6. The spell checker must not leak any memory.
7. The hash function has not been copied or search from anywhere. There are many ways to implement a hash function beyond using the first character (or characters) of a word. In example, consider a hash function that uses a sum of ASCII values or the length of a word. A good hash function tends to reduce “collisions” and has a fairly even distribution across hash table “buckets”.

Implementation in order:

- Implement load.
- Implement hash.
- Implement size.
- Implement check.
- Implement unload.

## Implementation Details and Choice

For insert and delete, the node enters the singly-linked list from the start. Therefore, we can say that the ssl is in fact a stack implementation, or a FIFO data structure. This makes the processes of insertion and deletion have O(1) time complexity.

For the hash function, there are many ways to optimize. The greatest issue in the code is the *collision resolution*. 

Collision resolution:
    
### Chaining:

In chaining, a linked list is maintained at each bucket of the hash table. When a collision occurs, the new element is simply appended to the linked list at that bucket. This approach is simple to implement and provides good performance when the hash table is appropriately sized and the load factor is low. However, as the load factor increases, the performance can degrade as the number of collisions increases and the length of the linked lists grows.

### Open Addressing:

In open addressing, when a collision occurs, the algorithm attempts to find another empty slot in the hash table to store the new element. There are different ways to find the next empty slot, such as linear probing, quadratic probing, and double hashing. The advantage of open addressing is that it avoids the memory overhead of maintaining linked lists, which can be significant for small elements. However, it requires careful tuning of the hash function and the probing sequence to ensure good performance.

### probing:

Probing is a general term for the process of searching for an empty slot in the hash table when a collision occurs. It is used in both open addressing and some variants of chaining. The idea is to search for an empty slot by looking at a sequence of buckets, starting from the one originally intended for the element. Different probing sequences can be used, such as linear probing (checking the next bucket), quadratic probing (checking buckets at increasing distances), or double hashing (using a second hash function to determine the distance between probes). The goal is to find an empty slot as quickly as possible while avoiding clustering, where groups of elements form "clusters" and make it harder to find empty slots.

### Cosine Similarity Method

The cosine similarity hashing method is based on computing the cosine similarity between a given vector (in this case, a vector representing a document or a word) and a set of randomly generated vectors (hash functions).

Here's a brief overview of the steps involved in cosine similarity hashing:

- Initialize a set of k random vectors, each of length n (where n is the dimensionality of the vectors being hashed).
- For each vector to be hashed, compute its dot product with each of the k random vectors. This yields k scalar values, each of which represents the cosine similarity between the input vector and a corresponding random vector.
- For each of the k scalar values obtained in step 2, set the corresponding bit in a binary hash code to 1 if the scalar value is greater than or equal to 0, and to 0 otherwise.
- The resulting binary hash code represents a compact signature of the input vector, which can be used for approximate nearest neighbor search.

Cosine similarity hashing has some advantages over traditional hash functions like those used in open addressing and chaining. In particular, it is relatively easy to implement and can yield high-quality hashes with low collision rates. However, it is generally less efficient than traditional hash functions in terms of both time and space complexity.

---

For the dictionary, it is common to use open addressing method.

---
