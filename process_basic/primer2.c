#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEFT	30000000
#define RIGHT	30000200

int main()
{
	int i,j,mark=0;
	pid_t pid;
	int st;

	for(i=LEFT;i<RIGHT;i++)
	{
		pid = fork();
		if(pid <0)
		{
			perror("fork()");
			exit(1);	
		}

		if (pid == 0)//child
		{
			mark = 1;
			for(j=2;j<i/2;j++)
			{
				if(i%j == 0)
				{
					mark = 0;
					break;
				}
			}
			if(mark)
				printf("%d is a primer\n",i);
			exit(0);
		}
	}
	
	for(i=LEFT;i<=RIGHT;i++)
	{
		wait(&st);
//		wait(NULL);
	}
	exit(0);
}


