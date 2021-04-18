#include <cs50.h>
#include <stdio.h>

int main(void)
{
	long long x = get_long_long("x: ");
	long long y = get_long_long("y: ");

	printf("%lli\n", x + y);
}
