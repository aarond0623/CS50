#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	// WRONG!
	/*
	char *s = get_string("s: ");
	char *t = s;
	t[0] = toupper(t[0]);
	printf("s: %s\n", s);
	printf("t: %s\n", t);
	*/

	char *s = get_string("s: ");
	char *t = malloc(strlen(s) + 1);
	if (t == NULL)
	{
		// malloc was unable to allocate memory.
		return 1;
	}
	// Manual copying
	/*
	for (int i = 0, n = strlen(s); i <= n; i++)
	{
		t[i] = s[i];
	}
	*/
	strcpy(t, s);
	t[0] = toupper(t[0]);
	printf("s: %s\n", s);
	printf("t: %s\n", t);
	free(t);
}
