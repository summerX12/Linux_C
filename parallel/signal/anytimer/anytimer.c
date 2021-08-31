#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#include "anytimer.h"

#define	RUN	1
#define	OVER	2
#define	CANCEL	3
	
struct itimerval value,ovalue;
struct mytimer_st *timer[JOB_MAX];
struct mytimer_st
{
	int sec;
	at_handler func;
	char *arg;
	int pos;
	int flag;
};

static void alrm_handler(int s)
{
	int i;

//	alarm(1);
	for(i=0;i<JOB_MAX;i++)
	{
		if(timer[i] != NULL)
		{
			if(timer[i]->flag == RUN)
			{
				timer[i]->sec--;		

				if(timer[i]->sec == 0)
				{
					timer[i]->flag = OVER;
					timer[i]->func(timer[i]->arg);
				}
			}
		}
	}
}

static int get_free_pos(void)
{
	int i;

	for(i = 0; i<JOB_MAX; i++)
	{
		if(timer[i] == NULL)
			return i;
	}
	return -1;
}

int inited=0;

void unload(void)
{
	setitimer(ITIMER_REAL,&ovalue,NULL);
}

int at_addjob(int sec,at_handler func,char *arg)
{
	struct mytimer_st *me;
	int id;

	if(!inited)
	{
		value.it_interval.tv_sec = 1;
		value.it_value.tv_sec = 1;
		signal(SIGALRM,alrm_handler);
		setitimer(ITIMER_REAL,&value,&ovalue);
//		alarm(1);
		inited = 1;

		atexit(unload);
	}
	if( (sec<0)||(func == NULL)||(arg == NULL) )
		return -EINVAL;

	id = get_free_pos();
	if(id < 0)
		return -ENOSPC;

	me = malloc(sizeof(*me));
	if(me == NULL)
		return -ENOMEM;
	
	me->sec = sec;
	me->func = func;
	me->arg = arg;
	me->pos = id;
	me->flag = RUN;
	timer[id] = me;	

	return id;
}

int at_canceljob(int id)
{
	if(id < 0)
		return -EINVAL;

	else if(timer[id]->flag == OVER)
		return -EBUSY;

	else if(timer[id]->flag == CANCEL)
		return -ECANCELED;

	else 
		timer[id]->flag = CANCEL;
	return 0;
}

int at_waitjob(int id)
{
	if(id < 0)
		return -EINVAL;

	timer[id] = NULL;
	free(timer[id]);

	return 0;
}


