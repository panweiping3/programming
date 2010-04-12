#include <syslog.h>

int main()
{
	int err = 1;

	if (err == 1)
	{
		syslog(LOG_USER, "%s\n", "fatal error occured");	
		
		return 1;
	}

}
