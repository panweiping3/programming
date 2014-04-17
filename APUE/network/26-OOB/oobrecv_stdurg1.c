/*
* oobrec.c
*
* echo 1 > /proc/sys/net/ipv4/tcp_stdurg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "common.h" 

extern void bail(char *on_what);
extern int BindAccept(char *addr);

static int s = -1;   /* Socket */
static int urg_mode = 0;
/*
 * echo 1 > /proc/sys/net/ipv4/tcp_stdurg
 */

static void sigurg_handler (int signo)
{
   signal(SIGURG, sigurg_handler);
   urg_mode = 1;
   return;
}

int main(int argc,char **argv)
{
   int z;   /* Status */
   char buf[256];

   fprintf(stderr, "I am waiting to recv ...\n");
   /*
   * Use a server address from the command
   * line,if one has been provided.
   * Otherwise,this program will default
   * to using the arbitrary address
   * 127.0.0.1:
   */
   s = BindAccept(argc >=2 ?argv[1] :"127.0.0.1");

   /*
   * Establish owership:
   */
   z = fcntl(s,F_SETOWN,getpid());
   if(z==-1)
       bail("fcntl(2)");

   /*
   * Catch SIGURG :
   */
   signal(SIGURG, sigurg_handler);
   for(;;)
   {
	memset(buf, '\0', sizeof(buf));
	if (urg_mode)
		z = recv(s,buf,sizeof(buf),MSG_OOB);
	else
		z = recv(s,buf,sizeof(buf),0);

       if(z==-1)
           bail("recv(2)");
       if(z==0)
        	break;
       buf[z] = '\0';
	
	if (urg_mode) {
       		printf("URG ''%s'' (%d) \n",buf,z);
		urg_mode = 0;
	} else
       		printf("recv ''%s'' (%d) \n",buf,z);
   }

   close(s);
   return 0;
}
