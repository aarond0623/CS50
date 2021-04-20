#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int collatz(int n, int steps);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        printf("%i\n", collatz(atoi(argv[1]), 0));
        return 0;
    }
    else
    {
        return 1;
    }
}

int collatz(int n, int steps)
{
    if (n == 1)
    {
        return steps;
    }
    else if (n % 2 == 0)
    {
        return collatz(n / 2, ++steps);
    }
    else
    {
        return collatz(3 * n + 1, ++steps);
    }
}
