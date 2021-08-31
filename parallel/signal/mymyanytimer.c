#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void f1(void *p)
{
	printf("f1():%s\n",p);
}

static void f2(void *p)
{
	printf("f2():%s\n",p);
}

static void alrm_handler(int s)
{
	static int i=0;

	i++;
	alarm(1);
	
	if(i == 2)
		f2("bbb");
	else if(i==5)
		f1("aaa");
	else if(i==7)
		f1("ccc");
}
int main()
{
	signal(SIGALRM,alrm_handler);
	alarm(1);

	puts("Begin!\n");
	//5s f1 "aaa"
	//2s f2 "bbb"
	//7s f1 "ccc"
	puts("End!\n");

	while(1)
	{
		write(1,".",1);
		sleep(1);
	}

	exit(0);
}
