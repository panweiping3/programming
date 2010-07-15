#include <stdio.h>

int main()
{
	int i=11;
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	switch (i) {
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	     default:
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	     case 12:
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	     case 13:
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	     case 14:
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	         ;
	 }

}
