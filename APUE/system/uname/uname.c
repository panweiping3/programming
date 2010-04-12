#include <stdio.h>
#include <sys/utsname.h>

int main()
{
	struct utsname uname_struct;

	if (uname(&uname_struct) == -1)
	{
		perror("uname error");
		return -1;
	}

	printf("%s\n", uname_struct.sysname);
	printf("%s\n", uname_struct.nodename);
	printf("%s\n", uname_struct.release);
	printf("%s\n", uname_struct.version);
	printf("%s\n", uname_struct.machine);
}
