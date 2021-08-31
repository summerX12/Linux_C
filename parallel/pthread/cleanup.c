#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

static void cleanup_func(void *p)
{
	puts(p);
}

static void *func(void *p)
{
	printf("thread is working\n");

	pthread_cleanup_push(cleanup_func,"cleanup:1");
	pthread_cleanup_push(cleanup_func,"cleanup:2");
	pthread_cleanup_push(cleanup_func,"cleanup:3");

	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tid;
	int err;

	puts("Begin\n");

	err = pthread_create(&tid,NULL,func,NULL);
	if(err)
	{
		fprintf(stderr,"pthread_creat():%s\n",strerror(err));
		exit(1);
	}
	pthread_join(tid,NULL);

	puts("End\n");

	exit(0);
}
