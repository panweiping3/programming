#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp_desktop = NULL;
	FILE *fp_xml = NULL;
	char buf[BUFSIZ] = {'\0'};
	char line[BUFSIZ] = {'\0'};
	char key[BUFSIZ/16] = {'\0'};
	char value[BUFSIZ/16] = {'\0'};
	char *p = NULL;

	if (argc != 3)
	{
		fprintf(stderr, "please check your arguments\n");
		exit(1);
	}

	if ((fp_desktop = fopen(argv[1], "r")) == NULL)	
	{
		fprintf(stderr, "fopen error: %s\n", argv[1]);
		exit(2);
	}

	if ((fp_xml = fopen(argv[2], "w+")) == NULL)
	{
		fprintf(stderr, "fopen error: %s\n", argv[2]);
		exit(3);
	}

	while (feof(fp_desktop) == 0)
	{
		memset(buf, '\0', BUFSIZ);
		memset(line, '\0', BUFSIZ);
		memset(key, '\0', BUFSIZ/16);
		memset(value, '\0', BUFSIZ/16);
		
		fgets(buf, BUFSIZ, fp_desktop);
	
		if ((strcmp(buf, "") == 0))		
			continue;

		if (strstr(buf, "[Desktop Entry]") != NULL)
		{		
			if (fputs("<group class=\"Desktop Entry\">\n", fp_xml) == EOF)
			{
				perror("fputs error");
				exit(5);
			}	
		}

		if ((p = strchr(buf, '=')) != NULL)
		{
			strncpy(key, buf, p-buf);
			fprintf(stdout, "key:%s\n", key);
			strncpy(value, p+1, buf+strlen(buf)-p);
			fprintf(stdout, "value:%s\n", value);
			
			snprintf(line, BUFSIZ/16, "\t<property name=\"%s\">\n", key);	

			if (fputs(line, fp_xml) == EOF)
			{
				perror("fputs error");
				exit(6);
			}	
			memset(line, '\0', BUFSIZ);
			value[strlen(value)-1] = '\0';
			snprintf(line, BUFSIZ/16, "\t\t<string>%s</string>\n", value);	

			if (fputs(line, fp_xml) == EOF)
			{
				perror("fputs error");
				exit(7);
			}	

			if (fputs("\t</property>\n", fp_xml) == EOF)
			{
				perror("fputs error");
				exit(8);
			}	
		}
	}
	
	if (fputs("</group>\n", fp_xml) == EOF)
	{
		perror("fputs error");
		exit(9);
	}	

}
