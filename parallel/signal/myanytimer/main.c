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
	mytimer_t *timer1,*timer2,*timer3;

	puts("Begin!\n");
	timer1 = timer_init();
	if(timer1 == NULL)
	{
		puts("timer1 creat fail\n");
		exit(1);
	}
	timer_set(timer1,5,f1,"aaa");
	

	timer2 = timer_init();
	if(timer2 == NULL)
	{
		puts("timer2 creat fail\n");
		exit(1);
	}
	timer_set(timer2,2,f2,"bbb");


	timer3 = timer_init();
	if(timer3 == NULL)
	{
		puts("timer3 creat fail\n");
		exit(1);
	}
	timer_set(timer3,7,f1,"ccc");

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
