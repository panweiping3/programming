#include <stdio.h>
#include <utmp.h>

int main(int argc, char *argv[])
{
		struct utmp *entry;

		setutent();

		while ((entry = getutent()) != NULL)
		{
			printf("%s ", entry->ut_user);
			printf("%s \n", entry->ut_line);
		}

		endutent();
		return 0;
}

