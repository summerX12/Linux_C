#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	FILE *fp;

	fp = fopen("tmp","w");
	if(fp == NULL)
	{
//	 	fprintf(stderr,"fopen() failed! errno = %d\n ",errno);
//		perror("fopen()");
	 	fprintf(stderr,"fopen():%s\n ",strerror(errno));
		exit(1);
	}
	puts("OK!");
	fclose(fp);
	exit(0);
}
