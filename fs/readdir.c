#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#define PAT	"/etc/"

int main(int argc,char *argv[])
{
	DIR *dp;
	struct dirent *readinfo;

	dp = opendir(PAT);
	if(dp == NULL)
	{
		perror("opendir()");
		exit(1);
	}
	
	while(1)
	{
		readinfo = readdir(dp);
		if(readinfo == NULL)
		{
			break;
		}
		puts(readinfo->d_name);
	}


	closedir(dp);

	exit(0);
}
