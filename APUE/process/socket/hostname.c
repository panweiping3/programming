#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
	char name[128];
	struct hostent *p = NULL;
	
	p = gethostent();

	fprintf(stdout, "hostname: %s\n", p->h_name);
	fprintf(stdout, "p address: %lx\n", p);

	if (gethostname(name, 128) < 0)
	{
		fprintf(stderr, "gethostname error\n");
		exit(1);
	}
	
	fprintf(stdout, "hostname: %s\n", name);
	
	if (getdomainname(name, 128) < 0)
	{
		fprintf(stderr, "getdomainname error\n");
		exit(1);
	}
	
	fprintf(stdout, "domainname: %s\n", name);
	exit(0);
}
