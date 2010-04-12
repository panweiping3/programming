#include <stdio.h>
	#include <stdlib.h>
#include <popt.h>

int main(int argc, const char **argv)
{
	char *interactive, *system_account;
	poptContext popt;
	struct poptOption options[] = {
		{"interactive", 'i', POPT_ARG_STRING, &interactive, 0,
		 "prompt for all information", NULL},
		{"reserved", 'r', POPT_ARG_STRING, &system_account, 0},
		POPT_AUTOHELP POPT_TABLEEND
	};

	popt = poptGetContext("popt", argc, argv, options, 0);
	poptSetOtherOptionHelp(popt, ("[OPTION...] user"));
	int c = poptGetNextOpt(popt);
	if (c != -1) 
	{
		fprintf(stderr, ("Error parsing arguments: %s.\n"), poptStrerror(c));
		poptPrintUsage(popt, stderr, 0);
		exit(1);
	}

	const char *name = NULL;
	name = poptGetArg(popt);

	fprintf(stdout, "interactive is:%s\n", interactive);
	fprintf(stdout, "system_account is:%s\n", system_account);
	fprintf(stdout, "name is:%s\n", name);
}
