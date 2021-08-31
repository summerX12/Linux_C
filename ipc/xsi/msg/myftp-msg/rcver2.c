#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto2.h"

int main()
{
	key_t key;
	int msgid;
	struct msg_s2c_st rbuf;

	key = ftok(KEYPATH,KEYPROJ);
	if(key <0)
	{
		perror("ftok()");
		exit(1);
	}

	msgid = msgget(key,IPC_CREAT|0600);//create  先运行，send方不用create
	if(msgid < 0)
	{
		perror("msgget()");
		exit(1);
	}

	while(1)
	{
		if(msgrcv(msgid,&rbuf,sizeof(rbuf)-sizeof(long),0,0) < 0)
		{
			perror("msgrcv()");
			exit(1);
		}

		if(rbuf.datalen == 0)
			break;
		else
			printf("rcv = %s\n",rbuf.data);

	}

	msgctl(msgid,IPC_RMID,NULL);

	exit(0);
}
