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
	sigset_t set,oset,saveset,tmpset;
	

	signal(SIGINT,int_handler);
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_UNBLOCK,&set,&saveset);
	sigprocmask(SIG_BLOCK,&set,&oset);

	while(1)
	{
		for(i=0; i<5; i++)
		{
			write(1,"*",1);
			sleep(1);
		}
		puts("\n");
		sigsuspend(&oset);
		/*
		sigprocmask(SIG_SETMASK,&oset,&tmpset);
		pause();
		sigprocmask(SIG_SETMASK,&tmpset,NULL);
		*/
	}
	sigprocmask(SIG_SETMASK,&saveset,NULL);
	exit(0);
}
