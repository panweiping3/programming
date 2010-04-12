#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int main()
{
	long int i, j;
	double f;
	clock_t start=0, end=0;
	start = clock();

	time_t now;
	
	printf(" CLOCKS_PER_SEC %lld\n", CLOCKS_PER_SEC);
	time(&now);

	printf("NOW is: %s\n", ctime(&now));
	
	for (j=0; j<100; ++j)
	{
		for (i=0; i<1000000; ++i)
		{
			f = sqrt(i);
		}
	}
	end = clock();

	printf("the process begins at %ld  end at %ld, used %f\n", 
			start, end, ((double)(end-start))/CLOCKS_PER_SEC);

	time(&now);
	printf("NOW is: %s\n", ctime(&now));

	return 0;
}
