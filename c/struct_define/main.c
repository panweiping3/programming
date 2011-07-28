#include <stdio.h>

#define A 20
struct HH{
    #define A 10
    int a;
};

int main()
{
  struct HH h;
  h.a=19;
	if (h.a > A) {
		fprintf(stderr, "%s %d %s big\n", __FILE__, __LINE__, __func__);
	}
  fprintf(stderr, "%s %d %s h.a=%d\n", __FILE__, __LINE__, __func__, h.a); 
  fprintf(stderr, "%s %d %s A=%d\n", __FILE__, __LINE__, __func__, A); 
//  fprintf(stderr, "%s %d %s h.A=%d\n", __FILE__, __LINE__, __func__, h.A); 
}
