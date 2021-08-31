#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/*
 * -y year
 * -m month
 * -d day
 * -H hour
 * -M min
 * -S second
 * */


#define BUFSIZE 	1024
#define FMTSTRSIZE	1024

int main(int argc,char **argv)
{
	time_t stamp;
	struct tm *tm;
	char timestr[BUFSIZE];
	int c;
	char fmtstr[FMTSTRSIZE];
	FILE *fp=stdout;

	fmtstr[0]='\0';//初始化成空串

	if(argc < 2)
	{
		fprintf(stderr,"Usage input para:-S/M/H/d/m/y\n");
		exit(1);
	}
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
 
	while(1)
	{
		c = getopt(argc,argv,"-H:MSy:md");
		if(c<0)
			break;

		switch(c)
		{
			case 1:
				fp = fopen(argv[optind-1],"w");
				if(fp == NULL)
				{
					perror("fopen()");
					fp = stdout;
				}
				break;
			case 'H':
				if(strcmp(optarg,"12") == 0)
					strncat(fmtstr,"%I(%P) ",10);
				else if(strcmp(optarg,"24") == 0)
					strncat(fmtstr,"%H ",10);
				else
					fprintf(stderr,"Invalid argument");
				break;
			case 'M':
				strncat(fmtstr,"%M ",10);
				break;
			case 'S':
				strncat(fmtstr,"%S ",10);
				break;
			case 'y':
				strncat(fmtstr,"%Y ",10);
				break;
			case 'm':
				strncat(fmtstr,"%m ",10);
				break;
			case 'd':
				strncat(fmtstr,"%d ",FMTSTRSIZE);
				break;
			default:
				break;

		}
	}

	strncat(fmtstr,"\n",10);
	strftime(timestr,BUFSIZE,fmtstr,tm);
	fputs(timestr,fp);
	
	if(fp != stdout)
		fclose(fp);

	exit(0);
}
