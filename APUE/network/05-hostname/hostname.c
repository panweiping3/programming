#include <stdio.h>
#include <unistd.h>

int main()
{
	char hostname[255] = {'\0'};
	gethostname(hostname, 255);
	
	printf("hostname is::%s\n", hostname);
}
