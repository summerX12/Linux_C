#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "anytimer.h"

static void f1(void *p)
{
	printf("f1():%s\n",p);
}

static void f2(void *p)
{
	printf("f2():%s\n",p);
}

int main()
{
	int timer1,timer2,timer3;

	puts("Begin!\n");

	timer1 = at_addjob(5,f1,"aaa");
	if(timer1<0)
	{
		fprintf(stderr,"timer1 creat fail:%s\n",-timer1);
		exit(1);
	}

	timer2 = at_addjob(2,f2,"bbb");
	if(timer2<0)
	{
		at_waitjob(timer1);
		fprintf(stderr,"timer2 creat fail:%s\n",-timer2);
		exit(1);
	}

	timer3 = at_addjob(7,f1,"ccc");
	if(timer3<0)
	{
		at_waitjob(timer1);
		at_waitjob(timer2);
		fprintf(stderr,"timer3 creat fail:%s\n",-timer3);
		exit(1);
	}

	at_canceljob(timer1);
	//5s f1 "aaa"
	//2s f2 "bbb"
	//7s f1 "ccc"
	puts("End!\n");

	while(1)
	{
		write(1,".",1);
		sleep(1);
	}

	at_waitjob(timer1);
	at_waitjob(timer2);
	at_waitjob(timer3);

	exit(0);
}
