# License

A program that proves the correct use of char* (string) usage and malloc, calloc, free usage.

## Learning Goals

- Practice working with files and file pointers
- More work with strings and arrays
- Debugging with debug50
- Use valgrind to check for memory leaks

## Background

Suppose you work for a company that develops AI-enhanced license plate recognition technology. As you develop your technology, you may want to use actual license plate numbers as test data. You have a text file with some plate numbers you want to analyze, so you first try reading from that text file and printing out the license plates, to test your file-reading logic. But when you run your program, only the last number prints 8 times! What went wrong?

## Implementation

First check for command-line arguments, since argv[1] should be the text file that contains the license plates. Then create a character array of length 7, since the plate numbers are 6 chars long and we need to save space for the NUL terminator. Now create an array of char *’s to store the 8 plate numbers. A file pointer is created to the external text file, then a variable to hold the index of each array element, and then the file is read and saves the plate numbers to the array.

Initially there were some memory leaks and bugs in the code that were resolved with the use of Valgrind.

## Usage

```lang-bash
$ ./license plates.txt
```
