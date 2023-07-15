#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
    // Test case 1
    {
        char input[] = "Carter\nCambridge\n";
        FILE* stream = fmemopen(input, strlen(input), "r");
        assert(stream != NULL);

        char buffer[100];
        setbuf(stdout, buffer);

        assert(main(stream) == 0);
        assert(strcmp(buffer, "Hello, Carter, from Cambridge!") == 0);

        fclose(stream);
    }

    // Test case 2
    {
        char input[] = "Margaret\nNew York\n";
        FILE* stream = fmemopen(input, strlen(input), "r");
        assert(stream != NULL);

        char buffer[100];
        setbuf(stdout, buffer);

        assert(main(stream) == 0);
        assert(strcmp(buffer, "Hello, Margaret, from New York!") == 0);

        fclose(stream);
    }

    return 0;
}