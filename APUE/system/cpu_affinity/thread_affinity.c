#define _GNU_SOURCE  
  
#include <stdio.h>  
#include <unistd.h>  
#include <sched.h>  
#include <pthread.h>    
#include <math.h>    
#include <assert.h>  
  
static int cpu_nums;  
  
static waste_time(long n)  
{  
    double res = 0;  
    long i = 0;  
  
    while(i <n * 200000) {  
        i++;  
        res += sqrt(i);  
    }  
  
    return res;  
}  
  
void *function1(void *argc)  
{  
     pthread_t  thread_id;  
     int ret, j, core;  
     cpu_set_t cpuset;  
   
     thread_id = pthread_self();  
     printf("porgran pid:%u, the function1 pthread id is %lu\n",getpid(), thread_id);  

     core = 0 % cpu_nums;  
     CPU_ZERO(&cpuset);  
     CPU_SET(core, &cpuset);  
   
     ret = pthread_setaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset);  
     assert(ret == 0);  
  
     /* Check the actual affinity mask assigned to the thread */  
     ret = pthread_getaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset);  
     assert(ret == 0);  
  
     printf("thread_id:%lu set the cpu:", thread_id);  
     for (j = 0; j < CPU_SETSIZE; j++)  
     if (CPU_ISSET(j, &cpuset))  
        printf(" CPU %d\n\n", j);   

     printf ("the function1 pthread id is %lu, bind core %d \n", thread_id, core );       
     printf("the function1 result: %f \n\n",waste_time (5000) );  
  
     return 0;  
}  
  
void *function2(void *argc)  
{  
  
     pthread_t  thread_id;  
     int ret, j, core;  
     cpu_set_t cpuset;  
  
     thread_id = pthread_self();  
     printf("porgran pid:%u, the function2 pthread id is %lu\n",getpid(), thread_id);  
  
     sleep(5);  
  
     core = 1 % cpu_nums;  
     CPU_ZERO(&cpuset);  
     CPU_SET(core, &cpuset);  
  
     ret = pthread_setaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset);  
     assert(ret == 0);  
  
     /* Check the actual affinity mask assigned to the thread */  
     ret = pthread_getaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset);  
     assert(ret == 0);  
  
     printf("thread_id:%lu set the cup:\n", thread_id);  
  
     for (j = 0; j < CPU_SETSIZE; j++)  
	     if (CPU_ISSET(j, &cpuset))  
		     printf(" CPU %d\n", j);  
  
  
     printf ("the function2 pthread id is %lu, bind core %d \n", thread_id, core);  
    printf ("the function2 result is: %f\n",waste_time (5000) );  
  
     return 0;  
}  
  
int main()  
{  
  
     pthread_t  thread_id[2];  
     int ret, j, core;  
     pthread_t main_thread_id;  
     cpu_set_t cpuset;  
     main_thread_id = pthread_self();  
  
     cpu_nums = sysconf(_SC_NPROCESSORS_CONF);  
     assert(cpu_nums > 0);  
  
     printf("cpu num:%d\n", cpu_nums);  
     core = 0 % cpu_nums;  
  
     printf("porgran pid:%u, mian_thread_id:%lu\n", getpid(), main_thread_id);  
     ret = pthread_create(thread_id, NULL, function1, NULL);  
     assert(ret == 0);  
  
     ret = pthread_create(thread_id + 1, NULL, function2, NULL);  
     assert(ret == 0);  
  
     ret = pthread_join(thread_id[0], NULL);  
     assert(ret == 0);  
  
     ret = pthread_join(thread_id[1], NULL);  
     assert(ret == 0);  
  
     core = 2 % cpu_nums;  
     CPU_ZERO(&cpuset);  
     CPU_SET(core, &cpuset);  
   
     ret = pthread_setaffinity_np(main_thread_id, sizeof(cpu_set_t), &cpuset);  
     assert(ret == 0);  
  
     /* Check the actual affinity mask assigned to the thread */  
     ret = pthread_getaffinity_np(main_thread_id, sizeof(cpu_set_t), &cpuset);  
     assert(ret == 0);  
  
     printf("mian_thread_id:%lu set the cpu:", main_thread_id);  
  
     for (j = 0; j < CPU_SETSIZE; j++)  
     if (CPU_ISSET(j, &cpuset))  
        printf(" CPU %d \n\n", j);  
  
     printf ("the main function pthread id is %lu, bind core %d result: %f\n", main_thread_id, core, waste_time (5000));  
  
     return 0;  
}  
