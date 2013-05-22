/*
* oobsend.c
*
* Example OOB sender:
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "common.h"

extern void bail(char *on_what);
extern int Connect(char *addr);

/*
* Send in-band data:
*/
static void iband(int s,char *str)
{
   int z;

   z = send(s,str,strlen(str),0);
   if(z==-1)
       bail("send(2)");

   printf("IB: ''%s'' (%d) \n",str,z);
   sleep(1);
}

/*
* Send out-of-band data:
*/
static void oband(int s,char *str)
{
   int z;

   z = send(s,str,strlen(str),MSG_OOB);
   if(z==-1)
       bail("send(2)");

   printf("OOB ''%s'' (%d)\n",str,z);
   sleep(1);
}

int main(int argc,char **argv)
{
   int s = -1;

   s = Connect(argc >=2
           ? argv[1]
           : "127.0.0.1");

   iband(s,"In the beginning");
   iband(s,"Linus begat Linux,");
   iband(s,"and the Penguins");

   oband(s,"rejoiced");

   iband(s,"exceedingly.");

   close(s);

   return 0;
}
