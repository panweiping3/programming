#include <stdio.h>
#include <unistd.h>

long get_sysconf(int NAME)
{
	long ret = -1;

	if ((ret = sysconf(NAME)) < 0)
	{
		perror("sysconf error");
		ret = -1;
	}

	return ret;
}

int main()
{
	long ret = -1;
	
	ret = get_sysconf(LOGIN_NAME_MAX);
	printf("_SC_LOGIN_NAME_MAX= %ld\n", ret);
	
	ret = get_sysconf(_SC_LOGIN_NAME_MAX);
	printf("_SC_LOGIN_NAME_MAX= %ld\n", ret);
	ret = get_sysconf(_SC_GETPW_R_SIZE_MAX);
	printf("_SC_GETPW_R_SIZE_MAX= %ld\n", ret);
	
	return 0;

}
