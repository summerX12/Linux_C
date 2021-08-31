#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc,char **argv)
{
	struct passwd *pwdline;

	if(argc < 2)
	{
		fprintf(stderr,"Usage input a uid, eg: 0,1000,1001\n");
		exit(1);
	}

	pwdline = getpwuid(atoi(argv[1]));
	if(pwdline == NULL)
	{
		perror("getpwuid()");
		exit(1);
	}
	
	puts(pwdline->pw_name);

	exit(0);
}


