#ifndef ANYTIMER_H_
#define ANYTIMER_H_


#define JOB_MAX	1024

typedef void (*at_handler)(void *);

int at_addjob(int sec,at_handler func,char *arg);
int at_canceljob(int id);
int at_waitjob(int id);


#endif
