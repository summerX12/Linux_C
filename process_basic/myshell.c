#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <glob.h>

#define DELIMS	" \t\n"

struct cmd_st
{
	glob_t globres;
};

static void prompt(void)
{
	printf("myshell-0.1$");
}

static void parse(char *line,struct cmd_st *res)
{
	char *tok;
	int i=0;

	while(1)
	{
		tok = strsep(&line,DELIMS);
		if(tok == NULL)
			break;
		if(tok[0] == '\0')
			continue;
		/*(*i) 只有第一次不追加GLOB_APPEND,以后每一次都APPEND */
		glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,&res->globres);
		i=1;
	}
}

int main()
{	
	char *linbuf = NULL;
	size_t linbuf_size = 0;
	pid_t pid;
//	glob_t globres;
	struct cmd_st cmd;

	while(1)
	{
		prompt();

		if(getline(&linbuf,&linbuf_size,stdin) < 0)
			break;

		parse(linbuf,&cmd);

		if(0)//内部命令
		{
			//do something
		}
		else//外部命令
		{
			pid = fork();
			if(pid < 0)
			{
				perror("fork");
				exit(1);
			}

			if(pid == 0)
			{
				execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
				perror("execvp()");
				exit(1);
			}
			else
				wait(NULL);
		}
	}
	exit(0);
}
