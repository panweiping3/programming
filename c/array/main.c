#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;

    int ary1[10] = {1,1,1,1,1,1};
   
    int *ppa = ary1;
    for (i=0; i<10; ++i) {
        fprintf(stderr, "%s %d %s:%d \n", __FILE__, __LINE__, __func__, *(ppa+i));   
    }

    int ary2[3][2] = {{1,2}, {3,4}, {5,6}};

    int (*pa)[2] = ary2;
    fprintf(stderr, "%s %d %s &ary2[0]=%x\n", __FILE__, __LINE__, __func__, &ary2[0]);   
    fprintf(stderr, "%s %d %s ary2[0]=%x\n", __FILE__, __LINE__, __func__, ary2[0]);   
    fprintf(stderr, "%s %d %s pa=%x\n", __FILE__, __LINE__, __func__, ary2[0]);

    fprintf(stderr, "%s %d %s ary2[0][0]=%d\n", __FILE__, __LINE__, __func__, ary2[0][0]);   
    fprintf(stderr, "%s %d %s ary2[0][1]=%d\n", __FILE__, __LINE__, __func__, ary2[0][1]);  

    fprintf(stderr, "%s %d %s address of ary2[0][0]=%x\n", __FILE__, __LINE__, __func__, &ary2[0][0]);   
    fprintf(stderr, "%s %d %s address of pa=%x\n", __FILE__, __LINE__, __func__, &pa[0][0]);   

    fprintf(stderr, "%s %d %s address of ary2[0][0]=%x\n", __FILE__, __LINE__, __func__, &ary2[1]); 
    fprintf(stderr, "%s %d %s address of pa=%x\n", __FILE__, __LINE__, __func__, &pa[1]);   
    fprintf(stderr, "%s %d %s address of pa=%x\n", __FILE__, __LINE__, __func__, *(&pa[1]));   
    fprintf(stderr, "%s %d %s address of pa=%x\n", __FILE__, __LINE__, __func__, pa + 1);   

    fprintf(stderr, "%s %d %s ary2[0][0]=%d\n", __FILE__, __LINE__, __func__, *pa);   
    fprintf(stderr, "%s %d %s ary[0][1]=%d\n", __FILE__, __LINE__, __func__, *(pa+1));   

	return 0;	
}
