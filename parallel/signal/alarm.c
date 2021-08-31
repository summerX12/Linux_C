#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	alarm(1);
	alarm(5);

	while(1);
		pause();

	exit(0);
}
