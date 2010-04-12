#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/kernel.h>

int kill(pid_t pid, int sig)
{
	int buf[32];
	sprintf(buf, "SPID:%d DPID:%d SIG:%d\n", getpid(), pid, sig);
	syslog(6, buf, strlen(buf));
	return syscall(SYS_kill, pid, sig);
}
