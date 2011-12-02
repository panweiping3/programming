/*
 * struct ST st;
 * If we know &st.member = addr,
 * how to get the address of st?
 * there are 2 ways:
 * 1 all c compiler support
 *      (int)&(((struct ST*)0)->member)
 * 2 gcc support
 *      __builtin_offsetof(struct ST, member)
 */

#include <stdio.h>

// get from kernel
#define container_of(ptr, type, member) ({          		\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

struct ST_TEST {
    int a;
    int b;
    int XXX;
    int member;
};

struct A  
{  
    int a;  
    int b;         
};  

int main()
{
    struct ST_TEST stTemp;
    fprintf(stderr, "%s %d %s &stTemp=%x\n", __FILE__, __LINE__, __func__, &stTemp);

    void *addMem = (char *)&stTemp.member;
    // now we assume that we do not know the address of stTemp,
    // but we know the address of stTemp.member,
    // we can make use of the address of stTemp.member to get the address of stTemp.
    
    // method 1
    char *address_of_stTemp = addMem - ((int)&((struct ST_TEST*)0)->member);
    fprintf(stderr, "%s %d %s &stTemp=%x\n", __FILE__, __LINE__, __func__, address_of_stTemp);

    // method 2
    address_of_stTemp = addMem - __builtin_offsetof(struct ST_TEST, member);
    fprintf(stderr, "%s %d %s &stTemp=%x\n", __FILE__, __LINE__, __func__, address_of_stTemp);
   
    // how to use container_of 
    struct ST_TEST *p = (struct ST_TEST*)container_of(addMem, struct ST_TEST, member);
    fprintf(stderr, "%s %d %s &stTemp=%x\n", __FILE__, __LINE__, __func__, p);

    struct A m;  
    printf("address of b 0x%x\n", (unsigned int)&(m.b));  
    printf("address of container m 0x%x\n", (unsigned int)&m);  
    printf("address of container m caculate from member b 0x%x\n", 
    		(unsigned int)container_of(&(m.b), struct A, b));  

    // if type of ptr != type->member, 
    // warining
    char *pp = (char *)&m.b;
    printf("address of container m caculate from member b 0x%x\n", 
    		(unsigned int)container_of(pp, struct A, b));  

    // if type doesn't have member
    // error
    printf("address of container m caculate from member b 0x%x\n", 
    		(unsigned int)container_of(&(m.b), struct A, c));  
    return 0;
}

