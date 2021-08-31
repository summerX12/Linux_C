#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc,char **argv)
{
	FILE *fp;
	char *linebuf;
	size_t linesize;

	if(argc<2)
	{
		fprintf(stderr,"Uasge...\n");
		exit(1);
	}

	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while(1)
	{
 		if(getline(&linebuf,&linesize,fp) < 0)
		{
			break;
		}
		else
		{
			printf("%d\n",strlen(linebuf));
		}
	}


	fclose(fp);
	exit(0);
}
