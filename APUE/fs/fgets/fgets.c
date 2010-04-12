#include <stdio.h>
#include <string.h>

int main()
{
	FILE *f = fopen("./shells", "r");
	
	if (f)
	{
		while (!feof(f))
		{
			char s[200];
			
			fgets(s, 200, f);
			
			if (feof(f))
				break;
		
			s[strlen(s)-1] = 0;
			
			printf("%s\n", s);
		}
		
		fclose(f);
	}

}
