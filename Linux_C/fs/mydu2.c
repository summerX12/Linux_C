#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

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
	struct stat statres;
	int64_t sum=0;
	char nextpath[PATHSIZE];
	DIR *des;
	struct dirent *readinfo;

	if(lstat(path,&statres) < 0)
	{
		perror("lstat()");
		exit(1);
	}
	if(!S_ISDIR(statres.st_mode))
	{
		return statres.st_blocks;
	}

	des = opendir(path);
	if(des == NULL)
	{
		perror("opendir()");
		exit(1);
	}
	
	while( (readinfo = readdir(des)) != NULL)
	{
		strcpy(nextpath,path);
		strcat(nextpath,"/");
		strcat(nextpath,readinfo->d_name);

		if(path_noloop(nextpath))
		{
			sum += mydu(nextpath);
		}
	}

	sum += statres.st_blocks;
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
