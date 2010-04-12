#include <sys/types.h>
#include <signal.h>

main()
{
	kill(getpid(), 9);
}
