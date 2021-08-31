#include <stdlib.h>
#include <stdio.h>
#include <glob.h>

#define PAT	"/etc/a*.conf"

int main(int argc,char **argv)
{
	int i,err;
	glob_t globres;

	err = glob(PAT,0,NULL,&globres);
	if(err < 0)
	{
		perror("glob()");
		exit(1);
	}

	for(i=0; i<globres.gl_pathc; i++)
		puts(globres.gl_pathv[i]);

	globfree(&globres);
	exit(0);
}
