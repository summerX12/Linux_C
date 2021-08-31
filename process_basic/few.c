#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
	pid_t pid;

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid == 0)//child
	{
		execl("/bin/date","date","+%s",NULL);
		perror("execl()");
		exit(1);
	}
	else
	{
		wait(NULL);
	}

	exit(0);
}



