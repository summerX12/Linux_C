#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char **argv)
{
	int err;
	pid_t pid;

	if(argc < 3)
	{
		fprintf(stderr,"Uasge ...\n");
		exit(1);
	}

	pid = fork();
	if(pid <0)
	{
		perror("fork()");
		exit(1);	
	}

	if(pid == 0)
	{
		setuid(atoi(argv[1]));
		execvp(argv[2],argv+2);
		perror("execvp()");
	}

	wait(NULL);

	exit(0);
}
