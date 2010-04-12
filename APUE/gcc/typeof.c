#include <stdio.h>
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

int main(int argc, char *argv[])
{
	fprintf(stdout, "min(3, 5)=%d\n", min(3, 5));
	fprintf(stdout, "min(3.0, 5.0)=%f\n", min(3.0, 5.0));
	
}
