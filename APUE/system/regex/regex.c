/* * 
 * * regular expression test in GNU C
 * */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <regex.h>

#define SUBSLEN 10
#define EBUFLEN 128 /* error buffer length */
#define BUFLEN 1024 /* matched buffer length */

int main (int argc, char **argv)
{
	char *s = "addsaffasdf";
	char *p = "a?d*f";
	
	if (match(s, p) == 0)
		printf("match\n");
	else
		printf("don't match\n");
	
	return 0;	
} 
	
int match(char *string, char *pattern)
{
	size_t len; /* store error message length */
	regex_t re; /* store compilned regular expression */
	regmatch_t subs[SUBSLEN]; /* store matched string position */
	char matched[BUFLEN]; /* store matched strings */
	char errbuf[EBUFLEN]; /* store error message */
	int err, i;

	printf ("String : %s\n", string);
	printf ("Pattern: %s\n", pattern);

	/* compile regular expression */
	err = regcomp (&re, pattern, REG_EXTENDED);

	if (err)
	{
		len = regerror (err, &re, errbuf, sizeof (errbuf));
		fprintf (stderr, "error: regcomp: %s\n", errbuf);
		exit (1);
	}
	
	printf ("Total has subexpression: %d\n", re.re_nsub);

	/* execute pattern match */
	err = regexec (&re, string, (size_t)SUBSLEN, subs, 0);

	if (err == REG_NOMATCH)
	{
		fprintf (stderr, "Sorry, no match ...\n");
		regfree (&re);
		exit (0);
	}
	else if (err)
	{
		len = regerror (err, &re, errbuf, sizeof (errbuf));
		fprintf (stderr, "error: regexec: %s\n", errbuf);
		exit (1);
	}

	/* if no REG_NOMATCH and no error, then pattern matched */
	printf ("\nOK, has matched ...\n\n");
	
	for (i = 0; i <= re.re_nsub; i++)
	{
		if (i == 0)
		{
			printf ("begin: %d, end: %d, ", subs[i].rm_so, subs[i].rm_eo);
		}
		else
		{
			printf ("subexpression %d begin: %d, end: %d, ", i, subs[i].rm_so, subs[i].rm_eo);
		}
	
		len = subs[i].rm_eo - subs[i].rm_so;
		memcpy (matched, string + subs[i].rm_so, len);
		matched[len] = '\0';
		printf ("match: %s\n", matched);
	}

	regfree(&re);
	exit(0);
}
