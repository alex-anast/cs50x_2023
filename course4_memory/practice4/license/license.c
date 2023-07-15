#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PLATE_LEN 7
#define FILE_SIZE 8

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[PLATE_LEN];

    // Create array to store plate numbers
    char *plates[FILE_SIZE];
    
    /* allocate and initialize */
    for (int i = 0; i < FILE_SIZE; i++)
    {
        plates[i] = (char *)calloc(PLATE_LEN, sizeof(char));
    }

    /* open the file */
    FILE *infile = fopen(argv[1], "r");
    /* error handling for opening the file */
    if (infile == NULL)
    {
        /* write to stderr which is the stdout in our case */
        fprintf(stderr, "Error opening the file\n");
        return 2;
    }

    /* for all the file size */
    for (int idx = 0; idx < FILE_SIZE; idx++)
    {
        /* license plate length is valid - returns the bytes written */
        if (fread(buffer, 1, PLATE_LEN, infile) != PLATE_LEN)
        {
            break;
        }
        /* indicate end of string on last character */
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
    }

    for (int i = 0; i < FILE_SIZE; i++)
    {
        printf("%s\n", plates[i]);
        /* free the allocated memory */
        free(plates[i]);
    }


    fclose(infile);
}
