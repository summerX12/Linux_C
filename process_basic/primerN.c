#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEFT	30000000
#define RIGHT	30000200
#define N	3

int main()
{
	int i,j,mark=0;
	pid_t pid;
	int n;

	for(n=0;n<N;n++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork()");
			//wait();
			exit(1);
		}

		if(pid == 0)
		{
			for(i=LEFT+n;i<=RIGHT;i+=N)
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
					printf("[%d]:%d is a primer\n",n,i);
			}
			exit(0);
		}
		
	}

	
	for(n=0;n<N;n++)
		wait(NULL);

	exit(0);
}


