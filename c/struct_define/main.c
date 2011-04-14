#include <stdio.h>

struct HH{
    #define A a 
    int a;
};

int main()
{
  struct HH h;
  h.a=19;

  fprintf(stderr, "%s %d %s h.a=%d\n", __FILE__, __LINE__, __func__, h.a); 
  fprintf(stderr, "%s %d %s h.A=%d\n", __FILE__, __LINE__, __func__, h.A); 
//  fprintf(stderr, "%s %d %s A=%d\n", __FILE__, __LINE__, __func__, A); 
}
