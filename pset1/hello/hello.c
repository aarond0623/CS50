#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for their name.
    string name = get_string("What is your name? ");
    printf("hello, %s\n", name);
}
