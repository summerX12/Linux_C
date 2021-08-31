#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define BUFSIZE 1024

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
		len = read(fds,buf,BUFSIZE);
		
		if(len < 0)
		{
			if(errno == EINTR)
				continue;
			else
			{
				perror("read()");
				break;
			}
		}
		
		if(len == 0)
			break;
		
		if(len > 0)	
			printf(buf);
	}

	close(fds);
	exit(0);
}




