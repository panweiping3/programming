 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <assert.h>
 

 struct helloworld_t
 {
     int num;
     char helloworld[0];
 };
 

 int main()
 {
     struct helloworld_t *p;
     unsigned int size = sizeof(struct helloworld_t) + sizeof("Hello World!\n");
     p = (struct helloworld_t *) malloc(size);
     if (!p)
            return -1;
 

     memcpy(p, "\x01\x00\x00\x00Hello World!\n", size);
 

     while (p->num--)
     {
         printf("%s",p->helloworld);
     }
    
	int i;
	memcpy((char *)&i, "\x09\x00\x00\x00", 4);
     printf("%d\n", i);
     free(p);
     return 0;
 }
