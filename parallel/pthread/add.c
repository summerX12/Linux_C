#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define THRNUM	20
#define FNAME		"tmp"
#define BUFSIZE	1024

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *handler(void *p)
{
	FILE *fp;
	char buf[BUFSIZE];

	fp = fopen(FNAME,"r+");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	pthread_mutex_lock(&mutex);

	fgets(buf,BUFSIZE,fp);
	fseek(fp,0,SEEK_SET);
	fprintf(fp,"%d\n",atoi(buf)+1);
	fclose(fp);

	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

int main()
{
	pthread_t tid[THRNUM];
	int i,err;

	for(i=0;i<THRNUM;i++)
	{
		err = pthread_create(tid+i,NULL,handler,NULL);
		if(err)
		{
			fprintf(stderr,"pthread_creat fail");
			exit(1);
		}
	}


	for(i=0;i<THRNUM;i++)
		pthread_join(tid[i],NULL);

	pthread_mutex_destroy(&mutex);

	exit(0);
}
