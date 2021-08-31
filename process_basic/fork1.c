#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	printf("[%d]:Begin!\n",getpid());
	
	fflush(NULL);

	pid = fork();
	if(pid<0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid == 0)
	{
		printf("[%d]:Child is working!\n",getpid());
	}
	else
	{
		printf("[%d]:Parent is working!\n",getpid());
	}

	printf("[%d]:end\n",getpid());

	exit(0);
}
