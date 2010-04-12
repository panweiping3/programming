#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 1024 

void skip_blank(char **p);
int get_cmd(char **line, char *cmd);
void get_argv(char *line, char argv[10][80]);
int anay_cmd(char *line, char *cmd, char argv[10][80]);
void do_cmd(char *cmd, char *argv[10]);

int main()
{
	char line[MAXLINE] = {'\0'};
	char argv[10][80];
	char cmd[10];

	printf("%% ");
	
	while (fgets(line, MAXLINE, stdin) != NULL)
	{
		line[strlen(line)-1] = '\0';
		
		memset(argv, '\0', 10*80);
		memset(cmd, '\0', 10);
	
		if (strcmp(line, "") != 0)
		{
			if (anay_cmd(line, cmd, argv) == 0)
			{
				do_cmd(cmd, argv);
			}
		}

		memset(line, '\0', MAXLINE);
		printf("%% ");
	}

	return 0;
}

void skip_blank(char **p)
{
	while ((**p) == ' ')
		(*p)++;
	
	return;
}

int get_cmd(char **line, char *cmd)
{
	char *p_start = NULL;
	char *p_end = NULL;
	char *line_end = NULL;

	line_end = (*line) + strlen(*line) -1;
	p_start = *line;
		
	if (strcmp(p_start, "") == 0)
		return -1;

	skip_blank(&p_start);

	p_end = strchr(p_start, ' ');

	if (p_end == NULL)
		p_end = line_end;
	
	strncpy(cmd, p_start, p_end-p_start+1);

	puts(cmd);
	
	*line = p_end + 1;
	return 0;
}

void get_argv(char *line, char argv[10][80])
{
	int i = 0;
	char *p_start = NULL;
	char *p_end = NULL;
	char *line_end = NULL;

	line_end = line + strlen(line);
	*line_end = ' ';
	p_start = line;
	skip_blank(&p_start); 

	if (strcmp(p_start, "") == 0)
		return;

	p_end = strchr(p_start, ' ');

	while (p_start != line_end)
	{
		strncpy(argv[i++], p_start, p_end-p_start+1);
		p_start = p_end;
		
		if (p_start == line_end)
			break;
		
		skip_blank(&p_start); 
		p_end = strchr(p_start, ' ');
	}

	for (;i>=0; i--)
		puts(argv[i]);

	return;
}

int anay_cmd(char *line, char *cmd, char argv[10][80])
{
	if (get_cmd(&line, cmd) == 0)
	{
		get_argv(line, argv);
		return 0;
	}

	return -1;
}

void do_cmd(char *cmd, char *argv[10])
{
	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid == 0)
		 {
			execvp(cmd, argv);
			perror("error");
			fprintf(stderr, "execlp error\n");
			exit(127);
		 }

	if ((pid = waitpid(pid, &status, 0)) < 0)
	{
		fprintf(stderr, "waitpid error\n");
		exit(2);
	}

	return;
}

