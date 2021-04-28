#include <stdio.h>

int main(void)
{
	int n = 50;
	int *p = &n;
	printf("%i\n", n);
	printf("%p\n", &n);
	printf("%p\n", p);
	printf("%i\n", *&n);

	char* s = "HI!";
	printf("%s\n", s);
	printf("%p\n", s);
	printf("%p\n", &s[0]);
	printf("%p\n", &s[1]);
	printf("%p\n", &s[2]);

	printf("%c", s[0]);
	printf("%c", s[1]);
	printf("%c\n", s[2]);

	printf("%c", *s);
	printf("%c", *(s + 1));
	printf("%c\n", *(s + 2));
}
