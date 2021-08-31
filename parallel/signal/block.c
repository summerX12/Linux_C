#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static  void int_handler(int s)
{
	write(1,"!",1);
}

int main ()
{
	int i;
	sigset_t set,oset,saveset;
	

	signal(SIGINT,int_handler);
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_UNBLOCK,&set,&saveset);

	while(1)
	{
		sigprocmask(SIG_BLOCK,&set,&oset);
		for(i=0; i<5; i++)
		{
			write(1,"*",1);
			sleep(1);
		}
		puts("\n");
		sigprocmask(SIG_SETMASK,&oset,NULL);
	}
	sigprocmask(SIG_SETMASK,&saveset,NULL);
	exit(0);
}
