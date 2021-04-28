#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *s = malloc(3);
	s[0] = 'H';
	s[1] = 'I';
	s[2] = '!';
	s[3] = '\0'; // Invalid write
	printf("%s\n", s); // Invalid read
	// Leaking 3 bytes of memory.
}
