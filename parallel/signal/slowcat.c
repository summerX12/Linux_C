#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define CPS	10
#define BUFSIZE CPS

static volatile int loop = 0;
static void alrm_handler(int s)
{
	alarm(1);
	loop = 1;
}

int main (int argc,char **argv)
{
	int fds=0;
	char buf[BUFSIZE];
	ssize_t len;

	if(argc<2)
	{
		fprintf(stderr,"Usage:...");
		exit(1);
	}

	signal(SIGALRM,alrm_handler);
	alarm(1);

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
		while(!loop);
			pause();
		loop = 0;

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




