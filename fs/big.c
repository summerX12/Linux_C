#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc,char **argv)
{
	int fd;
	off_t seek_val;

	if(argc < 2)
	{
		fprintf(stderr,"Uasge...\n");
		exit(1);
	}

	fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC, 0600);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	seek_val = lseek(fd,5LL*1024LL*1024LL*1024LL-1LL,SEEK_SET);
	if(seek_val < 0)
	{
		perror("lseek()");
		close(fd);
		exit(1);
	}

	write(fd,"",1);

	close(1);

	exit(0);
}
