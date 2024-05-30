#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *user = getenv("USER");
	printf("%s\n", user);
}