#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * date +%s
 **/

int main()
{
	puts("begin\n");

	execl("/bin/date","date","+%s",NULL);//从argv[0]开始。eg:ls -a;ls是argv[0]
	perror("execl()");
	exit(1);	


	puts("end\n");

	exit(0);
}
