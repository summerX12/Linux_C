#ifndef ANYTIMER_H_
#define ANYTIMER_H_


#define TIMER_MAX	1024

typedef void mytimer_t;
typedef void (*timeout_handler)(void *);

mytimer_t *timer_init(void);
int timer_set(mytimer_t *ptr,int sec,timeout_handler func,char *arg);
int timer_reset(mytimer_t *);

#endif
