#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PATHSIZE 	1024

static int path_noloop(const char *path)
{
	char *pos;

	pos = strrchr(path,'/');
	if(pos==NULL)
	{
		exit(1);
	}

	if( strcmp(pos+1,".") == 0 || strcmp(pos+1,"..")==0)
		return 0;

	return 1;
}

static int64_t mydu(const char *path)
{
	static int err;
	int i;
	glob_t globres;
	static struct stat statres;
	int64_t sum=0;
	static char nextpath[PATHSIZE];

	err = lstat(path,&statres);
	if(err < 0)
	{
		perror("lstat()");
		exit(1);
	}
	if(!S_ISDIR(statres.st_mode))
	{
	//	sum = statres.st_blocks;
	//	return sum;
		return statres.st_blocks;
	}

	strcpy(nextpath,path);
	strcat(nextpath,"/*");
	err = glob(nextpath,0,NULL,&globres);
	if(err < 0)
	{
		perror("glob()");
		exit(1);
	}

	strcpy(nextpath,path);
	strcat(nextpath,"/.*");
	err = glob(nextpath,GLOB_APPEND,NULL,&globres);
	if(err < 0)
	{
		perror("glob()");
		exit(1);
	}

	sum += statres.st_blocks;

	for(i=0; i<globres.gl_pathc; i++)
	{
//		if( (globres.gl_pathv[i] != ".")||(globres.gl_pathv[i] != "..") )	
		puts(globres.gl_pathv[i]);
		if(path_noloop(globres.gl_pathv[i]))
			 sum += mydu(globres.gl_pathv[i]);
	}

	return sum;
}

int main(int argc,char *argv[])
{

	if(argc < 2)
	{
		fprintf(stderr,"Usage...\n");
		exit(1);
	}

	printf("%lld\n",mydu(argv[1])/2);

	exit(0);
}
