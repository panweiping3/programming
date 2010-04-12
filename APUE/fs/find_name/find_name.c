#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// w = ?
// 8 = *

int match_8(char *source, int source_length, char *pattern, int pattern_length);
int match_w(char *source, int source_length, char *pattern, int pattern_length);

int main()
{
	char *source = "aexaybzce";
	char *pattern= "ad?a?b?ce";

	fprintf(stdout, "source: %s\n", source);	
	fprintf(stdout, "pattern: %s\n", pattern);	

	if (match_w(source, strlen(source), pattern, strlen(pattern)) == 0)
	{
		fprintf(stdout, "match\n");
		return 0;
	}
	else
	{
		fprintf(stdout, "don't match\n");
		return -1;
	}

	return -1;
}


int match_w(char *source, int source_length, char *pattern, int pattern_length)
{
	int i = 0;

	if (source_length != pattern_length)
		return -1;
	
	i = 0;	

	while (i < pattern_length)
	{
		if ((*(pattern+i)) == '?')
		{
			i++;	
			continue;
		}
		else if ((*(pattern+i)) == (*(source+i)))
			{
				i++;
				continue;
			}
			else
				return -1;	
	}

	if (i == pattern_length)
		return 0;

	return -1;
}
