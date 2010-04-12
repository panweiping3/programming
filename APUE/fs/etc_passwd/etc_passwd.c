#include <stdio.h>
#include <pwd.h>
#include <string.h>

int main()
{
	struct passwd *p = NULL;
	
	setpwent();

	while ((p = getpwent()) != NULL)
	{
		fprintf(stdout, "name: %20s ", p->pw_name);
		fprintf(stdout, " %10d ", p->pw_uid);
		fprintf(stdout, " %10d ", p->pw_gid);
		fprintf(stdout, " %20s ", p->pw_dir);
		fprintf(stdout, " %20s\n", p->pw_shell);
	}

	endpwent();

	fprintf(stdout, "500 : %s\n", getpwuid(500)->pw_name);	
	fprintf(stdout, "0 : %s\n", getpwuid(0)->pw_name);	

	return 0;
}

