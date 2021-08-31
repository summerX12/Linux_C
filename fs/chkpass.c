#include <stdlib.h>
#include <stdio.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

int main(int argc,char **argv)
{
	char *crypted_pass;
	char *input_pass;
	struct spwd* shadowline;

	if(argc<2)
	{
		fprintf(stderr,"Usage input uid\n");
		exit(1);
	}
	
	input_pass = getpass("PassWord:");

	shadowline = getspnam(argv[1]);

	crypted_pass = crypt(input_pass,shadowline->sp_pwdp);

	if(strcmp(shadowline->sp_pwdp,crypted_pass) == 0)
		puts("OK");
	else
		puts("Fail");
				
	exit(0);
}
