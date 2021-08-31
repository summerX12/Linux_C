#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "proto1.h"

int main()
{
	key_t key;
	msg_data_t sbuf;
	msg_eot_t eof;
	int msgid;

	key = ftok(KEYPATH,KEYPROJ);
	if(key < 0)
	{
		perror("ftok()");
		exit(1);
	}

	msgid = msgget(key,0);
	if(msgid < 0)
	{
		perror("msgget()");
		exit(1);
	}

	sbuf.mtype = MSG_DATA;
	strcpy(sbuf.data,"s");
	sbuf.datalen = 1;
	if( msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0) < 0)
	{
		perror("msgsnd()");
		exit(1);
	}

	sbuf.mtype = MSG_DATA;
	strcpy(sbuf.data,"e");
	sbuf.datalen = 1;
	if( msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0) < 0)
	{
		perror("msgsnd()");
		exit(1);
	}

	sbuf.mtype = MSG_DATA;
	strcpy(sbuf.data,"n");
	sbuf.datalen = 1;
	if( msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0) < 0)
	{
		perror("msgsnd()");
		exit(1);
	}

	sbuf.mtype = MSG_DATA;
	strcpy(sbuf.data,"d");
	sbuf.datalen = 1;
	if( msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0) < 0)
	{
		perror("msgsnd()");
		exit(1);
	}

	eof.mtype = MSG_EOF;
	if( msgsnd(msgid,&eof,sizeof(eof)-sizeof(long),0) < 0)
	{
		perror("msgsnd()");
		exit(1);
	}

	puts("ok\n");
	exit(0);
}
