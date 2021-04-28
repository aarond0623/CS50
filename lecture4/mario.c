#include <cs50.h>
#include <stdio.h>

void draw(int h);

int main(void)
{
	int height = get_int("Height: ");
	draw(height);
}

void draw(int h)
{
	// No base case. Will overflow the stack.
	draw(h - 1);

	for(int i = 0; i < h; i++)
	{
		printf("#");
	}
	printf("\n");
}
