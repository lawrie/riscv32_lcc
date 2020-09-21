#include <string.h>

/*
 * strndup - malloc and copy at most n characters of string s
 */
char *
strndup(const char *s, size_t n)
{
	char *p;

	p = (char*)malloc(n+1);
	if (p) {
		p[n] = 0;
		strncpy(p, s, n);
	}
	return p;
}
