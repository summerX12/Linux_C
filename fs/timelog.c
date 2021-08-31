#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define FILENAME	"tmp.txt"
#define BUFSIZE		1024

int main()
{
	FILE *fp;
	char buf[BUFSIZE];
	int linenum=0;
	time_t stamp;
	struct tm *tm;

	fp = fopen(FILENAME,"a+");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while( fgets(buf,BUFSIZE,fp) != NULL )
		linenum++;

	while(1)
	{
		stamp = time(NULL);
		if(stamp < 0)
			break;

		tm = localtime(&stamp);
		if(tm < 0)
			break;

		fprintf(fp,"%-4d%d-%d-%d %d:%d:%d\n",++linenum,\
			tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,\
			tm->tm_hour,tm->tm_min,tm->tm_sec);
		
		fflush(fp);
		sleep(1);
	}

	fclose(fp);

	exit(0);
}



