#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main (int argc,char **argv)
{
	int fds=0,fdd=0;
	char buf[BUFSIZE];
//	ssize_t  n=0;
	ssize_t ret=0,len=0;
	ssize_t pos=0;

	if(argc<3)
	{
		fprintf(stderr,"Usage:...");
		exit(1);
	}

	fds = open(argv[1],O_RDONLY);
	if(fds< 0)
	{
		perror("open()");
		exit(1);
	}


	fdd = open(argv[2],O_WRONLY|O_CREAT,O_TRUNC,0600);
	if(fdd < 0)
	{
		close(fds);
		perror("open()");
		exit(1);
	
	}

	while(1)
	{
		len = read(fds,buf,BUFSIZE);
		if(len < 0)
		{
			perror("read()");
			break;
		}
		if(len == 0)
			break;
		
		pos=0;
		while(len >0 )
		{
			ret = write(fdd,buf+pos,len);
			if(ret<0)
			{
				perror("write()");
				break;
			}
			pos += ret;
			len -= ret;
		}

	}
/**
	while(1)
	{
		len = read(fds,buf,BUFSIZE);
		if(len < 0)
		{
			perror("read()");
			break;
		}
		if(len == 0)
			break;
		
		ret = write(fdd,buf,len);
		if(ret<0)
		{
			perror("write()");
			break;
		}
	}
**/

/*
	while( (n=read(fds,buf,BUFSIZE)) > 0)
	{
		write(fdd,buf,n);
	}
*/
	close(fds);
	close(fdd);
	exit(0);
}




