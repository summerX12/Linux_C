#include <stdlib.h>
#include <stdio.h>

int main()
{
	int sysres;
	
	sysres = system("date +%s");
	if(sysres < 0)
		exit(1);

	exit(0);
}
