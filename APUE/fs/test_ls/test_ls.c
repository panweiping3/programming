#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define 	UID  	1
#define 	GID  	2
#define 	MAXLINE 128

void ls_file(char *filename);
void ls_dir(char *dirname);
void print_attr(struct stat *stat_buf_p);
void print_ino(struct stat *stat_buf_p);
void print_drw(struct stat *stat_buf_p);
void print_uid(struct stat *stat_buf_p);
void print_gid(struct stat *stat_buf_p);
void print_size(struct stat *stat_buf_p);
void print_mtime(struct stat *stat_buf_p);

int main(int argc, char *argv[])
{
	int i;
	struct stat stat_buf;

	if (argc < 2)
	{
		printf("please input a file name or dirtory name\n");
	
		return 0;
	}
	
	printf("%10s%4s%8s%8s%10s%16s%8s\n", "rw", "ln", "usr", "grp", "size", "time", "name");

	for (i=1; i<argc; i++)
	{
		bzero(&stat_buf, sizeof(struct stat));

		if (lstat(argv[i], &stat_buf) < 0)
		{
			perror("lstat error");
			continue;
		}

		if (S_ISDIR(stat_buf.st_mode) == 1)
			ls_dir(argv[i]);
		else 
			ls_file(argv[i]);
	}

	return 0;	
}

void ls_file(char *filename)
{
	struct stat stat_buf;

	if (filename == NULL)
		return;

	if (lstat(filename, &stat_buf) < 0)
	{
		fprintf(stderr, "111111111 lstat %s error\n", filename);
		
		return;
	}

	print_attr(&stat_buf);
	printf("    %-s\n", filename);

	return;
}

void ls_dir(char *dirname)
{
	struct stat stat_buf;

	if (dirname == NULL)
		return;

	fprintf(stdout, "\n");
	ls_file(dirname);	
	fprintf(stdout, "\n");

	// print dir's contents attr
	DIR *dir_p = NULL;
	struct dirent *dirent_p = NULL;

	if ((dir_p = opendir(dirname)) == NULL)
	{
		fprintf(stderr, "open dir %s error\n", dirname);
		return;
	}

	while ((dirent_p = readdir(dir_p)) != NULL)
	{
		if ((strcmp(dirent_p->d_name, ".") == 0) || (strcmp(dirent_p->d_name, "..") == 0))
			continue;	 

		char tmp[255] = {'\0'};
		strcat(tmp, dirname);
		if (dirname[strlen(dirname)-1] != '/')
			strcat(tmp, "/");
		strcat(tmp, dirent_p->d_name);
		
		if (lstat(tmp, &stat_buf) < 0)
		{
			fprintf(stderr, "2222222 lstat %s error\n", dirent_p->d_name);
			continue;
		}

		if (S_ISDIR(stat_buf.st_mode) == 1)
			ls_dir(tmp);
		else 
			ls_file(tmp);
	}

	closedir(dir_p);	

	return;
}

void print_attr(struct stat *stat_buf_p)
{
	print_drw(stat_buf_p);
	print_ino(stat_buf_p);
	print_uid(stat_buf_p);
	print_gid(stat_buf_p);
	print_size(stat_buf_p);
	print_mtime(stat_buf_p);

	return;
}

void print_drw(struct stat *stat_buf_p)
{
	// deal with d---------
	int i = 0;
	char rw[10];
	
	for (i=0; i<9; i++)
		rw[i] = '-';

	if (S_ISREG(stat_buf_p->st_mode) == 1)
		printf("-");
	else if (S_ISDIR(stat_buf_p->st_mode) == 1)
			printf("d");
	else if (S_ISCHR(stat_buf_p->st_mode) == 1)
			printf("c");
	else if (S_ISBLK(stat_buf_p->st_mode) == 1)
			printf("b");
	else if (S_ISFIFO(stat_buf_p->st_mode) == 1)
			printf("f");
	else if (S_ISLNK(stat_buf_p->st_mode) == 1)
			printf("l");
	else if (S_ISSOCK(stat_buf_p->st_mode) == 1)
			printf("s");
	else
		printf("bad file type");	

	if ((S_IRUSR & stat_buf_p->st_mode) != 0)
		rw[0] = 'r';
	if ((S_IWUSR & stat_buf_p->st_mode) != 0)
		rw[1] = 'w';
	if ((S_IXUSR & stat_buf_p->st_mode) != 0)
	{
		rw[2] = 'x';
		if ((S_ISUID & stat_buf_p->st_mode) != 0)
			rw[2] = 's';
	}
	if ((S_IRGRP & stat_buf_p->st_mode) != 0)
		rw[3] = 'r';
	if ((S_IWGRP & stat_buf_p->st_mode) != 0)
		rw[4] = 'w';
	if ((S_IXGRP & stat_buf_p->st_mode) != 0)
	{
		rw[5] = 'x';
		if ((S_ISGID & stat_buf_p->st_mode) != 0)
			rw[5] = 's';
	}
	if ((S_IROTH & stat_buf_p->st_mode) != 0)
		rw[6] = 'r';
	if ((S_IWOTH & stat_buf_p->st_mode) != 0)
		rw[7] = 'w';
	if ((S_IXOTH & stat_buf_p->st_mode) != 0)
		rw[8] = 'x';
	
	rw[9] = '\0';	
	printf("%s", rw);

	return;
}

void print_ino(struct stat *stat_buf_p)
{
	printf("%4d", stat_buf_p->st_nlink);
}

void print_uid(struct stat *stat_buf_p)
{
	char *p_start = NULL;
	char *p_end = NULL;
	char name[32];
	char uid[32];
	char buf[32];
	char line[MAXLINE];
	FILE *fp = NULL;

	bzero(name, 32);
	bzero(uid, 32);
	bzero(buf, 32);

	snprintf(uid, 32, "%d", stat_buf_p->st_uid);

	if ((fp = fopen("/etc/passwd", "r")) == NULL)
	{
		perror("open /etc/passwd error");
		exit(3);
	}
	
	while (fgets(line, MAXLINE, fp) != NULL)
	{
		p_start = strstr(line, ":x:");
		
		p_start += 3; 
		
		p_end = strchr(p_start, ':');
		strncpy(buf, p_start, p_end-p_start);

		if (strncmp(buf, uid, strlen(uid)) == 0)
		{
			p_end = strchr(line, ':');
			strncpy(name, line, p_end-line);
			printf("%8s", name);
			break;
		}
		
		bzero(line, MAXLINE);
	}
	
	fclose(fp);

	return;
}

void print_gid(struct stat *stat_buf_p)
{
	char *p_start = NULL;
	char *p_end = NULL;
	char name[32];
	char gid[32];
	char buf[32];
	char line[MAXLINE];
	FILE *fp = NULL;

	bzero(name, 32);
	bzero(gid, 32);
	bzero(buf, 32);

	snprintf(gid, 32, "%d", stat_buf_p->st_gid);

	if ((fp = fopen("/etc/group", "r")) == NULL)
	{
		perror("open /etc/group error");
		exit(3);
	}
	
	while (fgets(line, MAXLINE, fp) != NULL)
	{
		p_start = strchr(line, ':');
		p_start = strchr(p_start+1, ':');
		
		p_start++;; 
		
		p_end = strchr(p_start, ':');
		strncpy(buf, p_start, p_end-p_start);

		if (strncmp(buf, gid, strlen(gid)) == 0)
		{
			p_end = strchr(line, ':');
			strncpy(name, line, p_end-line);
			printf("%8s", name);
			break;
		}
		
		bzero(line, MAXLINE);
	}

	fclose(fp);

	return;
}

void print_size(struct stat *stat_buf_p)
{
	printf(" %10d", stat_buf_p->st_size);
}

void print_mtime(struct stat *stat_buf_p)
{
	char time[26];
	
	bzero(time, 26);
	ctime_r(&stat_buf_p->st_mtime, time);
	time[24] = '\0';

	printf(" %s", &time[10]);
}
