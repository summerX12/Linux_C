#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int loop = 1;
static void alrm_handler(int s)
{
	loop = 0;
}

int main()
{
	int64_t count = 0;

	alarm(5);
	signal(SIGALRM,alrm_handler);


	while(loop)
		count++;


	printf("%lld\n",count);
	exit(0);
}
