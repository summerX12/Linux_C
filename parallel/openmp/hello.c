#include <stdio.h>
#include <stdlib.h>

int main()
{
#pragma omp paralle
{
	puts("Hello");
	puts("World");
}	

	exit(0);
}
