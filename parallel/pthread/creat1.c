#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void *func(void *p)
{
	puts("thread1\n");
//	return NULL;
	pthread_exit(NULL);
}

int main()
{	
	pthread_t ptid;
	int err;

	puts("Begin\n");
	err = pthread_create(&ptid,NULL,func,NULL);
	if(err<0)
	{
		fprintf(stderr,"pthread_creat err:%s",strerror(err));
		exit(1);
	}
	pthread_join(ptid,NULL);
	puts("End\n");

	exit(0);
}
