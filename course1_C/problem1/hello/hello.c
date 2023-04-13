#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string user_input = get_string("Ẅhat is your name? ");
    printf("hello, %s\n", user_input);
    return 0;
}
