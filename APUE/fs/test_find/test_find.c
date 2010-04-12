#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex.h>

#define SUBSLEN 10
#define EBUFLEN 128 /* error buffer length */
#define BUFLEN 1024 /* matched buffer length */
int match(char *string, char *pattern);
int process_regular_expression(char *reg_exp);

int main(int argc, char *argv[])
{
	int i = 0;
	char *dir = NULL;
	char file_name[256] = {'\0'};
	DIR *dir_p = NULL;
	struct dirent *dirent_p = NULL;

	if ((i < 3) && (i > 4))
	{
		fprintf(stderr, "input arguments incorrect\n");
		exit(1);
	}

	if (argc == 3)
	{
		if (strcmp(argv[1], "-name") != 0)
		{
			fprintf(stderr, "input arguments incorrect\n");
			exit(2);
		}
		else
		{
			dir = "./";
			strncpy(file_name, argv[2], 256);
			
			if (process_regular_expression(file_name) != 0)
				exit(4);
		}
	}
	else if (argc == 4)
		{
			if (strcmp(argv[2], "-name") != 0)
			{
				fprintf(stderr, "input arguments incorrect\n");
				exit(3);
			}
			else
			{
				dir = argv[1];
				strncpy(file_name, argv[3], 256);

				if (process_regular_expression(file_name) != 0)
					exit(4);
			}
		}

	if ((dir_p = opendir(dir)) == NULL)
	{
		fprintf(stderr, "open dir %s error\n", dir);
		exit(4);
	}
	
	while ((dirent_p = readdir(dir_p)) != NULL)
	{
		if ((strcmp(dirent_p->d_name, ".") == 0) || (strcmp(dirent_p->d_name, "..") == 0))
			continue;
		
		if (match(dirent_p->d_name, file_name) == 0)
			fprintf(stdout, "%s\n", dirent_p->d_name);
	}

	closedir(dir_p);

	return 0;
}

int process_regular_expression(char *reg_exp)
{
	char reg[256] = {'\0'};

	int size = strlen(reg_exp);
	int i = 0;
	int j = 0;

	reg[j] = '^';
	j++;

	for (i=0; i<size; i++)
	{
		if (reg_exp[i] == '.')
		{
			reg[j++] = '\\';
			reg[j++] = '.';
			continue;
		}

		if (reg_exp[i] == '?')
		{
			reg[j++] = '.';
			reg[j++] = '{';
			reg[j++] = '1';
			reg[j++] = '}';
			continue;
		}

		if (reg_exp[i] == '*')
		{
			reg[j++] = '.';
			reg[j++] = '*';
			continue;
		}

		//  illegal charactor handling
		reg[j++] = reg_exp[i];
	}
	
	reg[j++] = '$';
	reg[j] = '\0';

	strncpy(reg_exp, reg, 256);

	return 0;
}


int match(char *string, char *pattern)
{
	size_t len; /* store error message length */
	regex_t re; /* store compilned regular expression */
	regmatch_t subs[SUBSLEN]; /* store matched string position */
	char matched[BUFLEN]; /* store matched strings */
	char errbuf[EBUFLEN]; /* store error message */
	int err = 0;


	/* compile regular expression */
	err = regcomp (&re, pattern, REG_EXTENDED);

	if (err)
	{
		len = regerror (err, &re, errbuf, sizeof (errbuf));
		return -1;
	}
	
	/* execute pattern match */
	err = 0;
	err = regexec (&re, string, (size_t)SUBSLEN, subs, 0);

	if (err == REG_NOMATCH) 
	{
		regfree (&re);
		return -1;
	}

	return 0;
}
