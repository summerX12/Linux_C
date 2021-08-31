#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 	1024

int main(int argc,char **argv)
{
	int fd1,fd2;
	char buf[BUFSIZE],tmp[BUFSIZE];
	ssize_t n_all=0,n_10line=0,n_11line=0,n_write=0,n_read=0;
	int n_cur=0,line_num=1,line_flag=0;
	off_t n_line10=0,n_line11=0;
	off_t del_byte=0,del_flag=0;

	if(argc<2)
	{
		fprintf(stderr,"Usage ...\n");
		exit(1);
	}

	fd1 = open(argv[1],O_RDONLY);
	if(fd1<0)
	{
		perror("open()");
		exit(1);
	}

	fd2 = open(argv[1],O_RDWR);
	if(fd2<0)
	{
		perror("open()");
		exit(1);
	}


	n_all = read(fd1,buf,BUFSIZE);
	if(n_all < 0)
	{
		perror("read()");
		exit(1);
	}

	for(n_cur=0;n_cur<n_all;n_cur++)
	{
		if(buf[n_cur]== '\n')
		{
			line_num++;
		}
		if( (line_num == 10)&&(line_flag == 0) )
		{
			line_flag = 1;
			n_10line = n_cur+1;	
		}
		else if(line_num == 11)
		{
			n_11line = n_cur+1;
			break;
		}		
	}


	n_line11 = lseek(fd1,n_11line,SEEK_SET);
	if(n_line11 != n_11line)
	{
		perror("lseek()");
		exit(1);
	}

	n_line10 = lseek(fd2,n_10line,SEEK_SET);
	if(n_line10 != n_10line)
	{
		perror("lseek()");
		exit(1);
	}

	while(1)
	{
		n_read = read(fd1,tmp,BUFSIZE);
		n_write = write(fd2,tmp,n_read);	

		if( (n_read <= 0) || (n_write <= 0) )
		{
			break;
		}
	}

	del_byte = n_11line - n_10line;
	del_flag = ftruncate(fd2,n_all-del_byte);
	if(del_flag < 0)
	{
		perror("del_flag()");
		exit(1);
	}

	close(fd1);
	close(fd2);

	exit(0);

}
