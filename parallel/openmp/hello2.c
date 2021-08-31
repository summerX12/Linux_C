#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>

int main()
{
#pragma omp paralle sections
{
#pragma omp section
	puts("hello");
//	printf("[%d]Hello\n",omp_get_thread_num());
#pragma omp section
	puts("world");
//	printf("[%d]World\n",omp_get_thread_num());
}	

	exit(0);
}
