#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "anytimer.h"

struct mytimer_st *timer[TIMER_MAX];
struct mytimer_st
{
	int sec;
	timeout_handler func;
	char *arg;
	int pos;
};

static void alrm_handler(int s)
{
	int i;

	alarm(1);

	for(i=0;i<TIMER_MAX;i++)
	{
		if(timer[i] != NULL)
		{
			timer[i]->sec--;

			if(timer[i]->sec == 0)
			{
				timer[i]->func(timer[i]->arg);
				timer[i]->sec = 0;
				timer[i]->func = NULL;
				timer[i]->arg = NULL;
			}
		}
	}

}

static int get_free_pos(void)
{
	int i;

	for(i = 0; i<TIMER_MAX; i++)
	{
		if(timer[i] == NULL)
			return i;
	}
	return -1;
}

mytimer_t *timer_init(void)
{
	struct mytimer_st *me;
	int pos;

	signal(SIGALRM,alrm_handler);
	alarm(1);

	pos = get_free_pos();
	if(pos < 0)
		return NULL;

	me = malloc(sizeof(*me));
	if(me == NULL)
		return NULL;
	
	me->pos = pos;

	timer[pos] = me;	
	return me;

}


int timer_set(mytimer_t *ptr,int sec,timeout_handler func,char *arg)
{
	struct mytimer_st *me = ptr;

	me->sec = sec;
	me->func = func;
	me->arg = arg;

}

int timer_reset(mytimer_t *ptr)
{
	struct mytimer_st *me = ptr;

	timer[me->pos] = NULL;
	free(me);

	return 0;
}


/*
void timer_free(void)
{
	int i;

	for(i=0; i<TIMER_MAX; i++)
	{
		free(timer[i]);
	}
}
*/
