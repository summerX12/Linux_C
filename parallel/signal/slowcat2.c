#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define CPS	10
#define BUFSIZE CPS
#define BURST	100

static volatile sig_atomic_t token = 0;

static void alrm_handler(int s)
{
//	alarm(1);
	token++;
	if(token > BURST)
		token = BURST;
}

int main (int argc,char **argv)
{
	int fds=0;
	char buf[BUFSIZE];
	ssize_t len;
	struct itimerval itv;

	if(argc<2)
	{
		fprintf(stderr,"Usage:...");
		exit(1);
	}

	signal(SIGALRM,alrm_handler);
//	alarm(1);

	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;

	if(setitimer(ITIMER_REAL,&itv,NULL) < 0)
	{
		perror("setitimer()");
		exit(1);
	}

	do{
		fds = open(argv[1],O_RDONLY);
		if(fds< 0)
		{
			if(errno != EINTR)
			{
				 perror("open()");
				 exit(1);
			}
		}
	}while(fds<0);


	while(1)
	{
		while(token <= 0);
			pause();
		token--;

		while((len = read(fds,buf,BUFSIZE)) < 0 )
		{
			if(len < 0)
			{
				if(errno == EINTR)
					continue;
				perror("read()");
				break;
			}
		}
		if(len == 0)
			break;
		
		if(len > 0)	
		{
			printf(buf);
			fflush(NULL);
		}
	}

	close(fds);
	exit(0);
}




