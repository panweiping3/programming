#include<stdio.h> 
typedef struct { 
  char i; 
  int j; 
  char k; 
}Test; 

int main() 
{ 
  Test *p = 0; 
  printf("p->i %x\n", &(p->i)); 
//  printf("p->i %x %x\n", &(p->i), __builtin_offsetof(Test, i)); 
//  printf("p->j %x %x\n", &(p->j), __builtin_offsetof(Test, j)); 
//  printf("p->k %x %x\n", &(p->k), __builtin_offsetof(Test, k)); 

  return 0;
} 
