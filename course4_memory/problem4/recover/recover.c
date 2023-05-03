#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 512

typedef uint8_t byte_t;

/* define jpg signature pattern as a static constant global */
static const byte_t JPG_SIGNATURE_PATTERN[] = {0xff, 0xd8, 0xff, 0xe0};

int check_if_jpg_start(void *buffer);
int write_jpg(int count, void *buffer);

int main(int argc, char *argv[])
{
    /* accept exactly one command-line argument */
    if (argc != 2)
    {
        /* remind the user of the correct usage */
        fprintf(stderr, "Usage: ./recover <file.raw>\n");
        /* and return error code 1, as per specifications */
        return 1;
    }

    /* define file variables */
    FILE *file_raw = NULL;  // best practice : always set pointers to NULL...
    FILE *file_jpg = NULL;  // ...if not immediately used.

    /* open the forensic raw image */
    file_raw = fopen(argv[1], "r");
    /* check if file could not be opened */
    if (file_raw == NULL)
    {
        /* inform the user */
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        /* and return status code 1, as per the specification */
        return 1;
    }

    /* open buffer for the incoming data - not forgetting the NUL character on strings */
    byte_t *buffer = (byte_t *)calloc(BLOCK_SIZE, sizeof(byte_t));
    /* error handling on memory allocation */
    if (buffer == NULL)
    {
        /* notify user about count number */
        fprintf(stderr, "Memory allocation error\n");
        /* and return default error code */
        return 1;
    }

    /* define and initialize variable to count the jpgs that are met */
    /* needs one less than zero because of the start of the process */
    int count_jpg = -1; // first one will be 000.jpg

    int in_jpgs = 0;

    /* file read into buffer every 512 B */
    while (fread(buffer, 1, BLOCK_SIZE, file_raw) == BLOCK_SIZE)
    {
        /* chech if the block is the start of a jpg */
        if (check_if_jpg_start(buffer))
        {
            /* indicate the start of writing */
            in_jpgs = 1;    // setting the number again and again - overhead

            /* add to numbering - changes filename */
            count_jpg++;
        }
        /* if the writing has started in general */
        if (in_jpgs == 1)
        {
            /* write the jpg in appending mode with the next */
            int status = write_jpg(count_jpg, buffer);
            if (status == 0)
            {
                fprintf(stderr, "Error in writing the jpg, exiting\n");
                return 1;
            }
        }
    }

    /* free the buffer used */
    free(buffer);

    /* close the raw data file */
    fclose(file_raw);
}

/**
 * @brief check if buffer contains a jpg
 * 
 * @param buffer 
 * @return int 
 */
int check_if_jpg_start(void *buffer)
{
    /* have to tell it that it contains bytes */
    byte_t *local_buffer = (byte_t *)buffer;

    /* check the first three bytes */
    if (memcmp(local_buffer, JPG_SIGNATURE_PATTERN, 3) != 0)
    {
        return 0;
    }

    /* set a temp to the 4th byte's first half */
    byte_t half_byte = local_buffer[3] & 0xf0;
    /* check if the half byte is matching the signature pattern */
    if (half_byte != JPG_SIGNATURE_PATTERN[3])
    {
        return 0;
    }

    /* if not returned yet, that means it is a match! Return true */
    return 1;
}

/**
 * @brief write jpg and use count as parameter to name the file
 * 
 * @param count 
 * @param buffer 
 * @return int status
 */
int write_jpg(int count, void *buffer)
{
    /* set the structure of the buffer */
    byte_t *local_buffer = (byte_t *)buffer;

    /* set up name string */
    char *jpg_name = (char *)calloc(8, sizeof(char));
    /* error handling on memory allocation */
    if (jpg_name == NULL)
    {
        /* notify user about count number */
        fprintf(stderr, "Memory allocation error\n");
        /* and return default error code */
        return 0;
    }

    /* get name in format ###.jpg where ### is the numbering of the jpg */
    snprintf(jpg_name, 8, "%03d.jpg", count);

    /* open file with correct name for writing */
    FILE *file_jpeg = fopen(jpg_name, "a");
    /* error handling on opening the file */
    if (file_jpeg == NULL)
    {
        /* notify the user */
        fprintf(stderr, "Error opening the file to write: %s\n", jpg_name);
        /* valgrind didn´t catch this : have to close memory before return ! */
        free(jpg_name);
        /* return error status */
        return 0;
    }
            
    /* try to write to the jpg file */
    if (fwrite(
            local_buffer,   // obtain the data from
            sizeof(byte_t), // size of single data item
            BLOCK_SIZE,     // number of items of data
            file_jpeg       // file to write
        ) != BLOCK_SIZE
       ) /* if failed to write */
    {
        /* notify the user about failure */
        fprintf(stderr, "Failed to write JPEG\n");
        /* close the file */
        fclose(file_jpeg);
        /* handle the memory */
        free(jpg_name);
        /* and return error status */
        return 0;
    }

    /* free the name string */
    free(jpg_name);

    /* close the jpeg file */
    fclose(file_jpeg);

    /* return success*/
    return 1;
}
