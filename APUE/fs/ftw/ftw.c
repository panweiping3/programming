#include <stdio.h>
#include <ftw.h>
int  fn(const char *file, const struct stat *sb, int flag)
{
	printf("%s\n", file);

	return 0;
}

int main()
{
	ftw("/home/pwp/gtest",  fn, 1000);
}


