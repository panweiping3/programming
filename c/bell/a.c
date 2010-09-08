#include <stdio.h>
int main()
{
		int i;
		for (i=0;i<10;i++)
		{
				sleep(1);
				fprintf(stdout,"\7");
		}
		printf ("run to here \n");
}
