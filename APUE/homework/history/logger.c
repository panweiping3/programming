#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>

//int execve(const char *filename, char *const argv[], char *const envp[]); 

typedef int (*func)(const char *filename, char *const argv [], char *const envp[]);
       
int execve(const char *filename, char *const argv [], char *const envp[])
{
	func real_execve;
	void *handle = NULL;

	handle = dlopen("/lib/libc.so.6", RTLD_NOW);
	real_execve = (func)dlsym(handle, "execve");

	if (real_execve == NULL)
	{
		fprintf(stderr, "can't find execve function\n");
		return -2;
	}
	
	FILE *fp = fopen("/tmp/program.log", "a+");

	fwrite(filename, sizeof(char), strlen(filename), fp);
	fputs("\n", fp);
	fclose(fp);

	int ret = real_execve(filename, argv, envp);

	return ret;
}

