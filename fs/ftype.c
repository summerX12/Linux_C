#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int ftype(const char* fname)
{
	struct stat buf;
	int type=0;

	if(stat(fname,&buf) < 0)
	{
		perror("stat()");
		exit(1);
	}

	if( S_ISREG(buf.st_mode) )
		return '-';
	else if( S_ISDIR(buf.st_mode) )
		return 'd';
	else if( S_ISCHR(buf.st_mode) )
		return 'c';
	else if( S_ISBLK(buf.st_mode) )
		return 'b';
	else if (S_ISFIFO(buf.st_mode))
		return 'p';	
	else if (S_ISLNK(buf.st_mode))
		return 'l';
	else if (S_ISSOCK(buf.st_mode))
		return 's';
	else
		return '?';
}

int main(int argc,char **argv)
{
	int fd;

	if(argc < 2)
	{
		fprintf(stderr,"Usage...\n");
		exit(1);
	}

	fd = open(argv[1],O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	printf("%c\n",ftype(argv[1]));

	close(fd);
	exit(0);
}
