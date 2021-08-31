#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUFSIZE 	1024

int main()
{
	time_t stamp;
	struct tm *tm;
	char timestr[BUFSIZE];

	time(&stamp);
	if(stamp == 0)
	{
		perror("time()\n");
		exit(1);
	}

	tm = localtime(&stamp);
	if(tm < 0)
	{
		perror("localtime()\n");
		exit(1);
	}

	strftime(timestr,BUFSIZE,"NOW:%Y-%m-%d",tm);
	puts(timestr);

	tm->tm_mday+=100;
	(void)mktime(tm);
	strftime(timestr,BUFSIZE,"100 days later:%Y-%m-%d",tm);
	puts(timestr);

	exit(0);
}
