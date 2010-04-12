#include <stdio.h>  
#include <stdlib.h>  
#include <semaphore.h>  
#include <pthread.h>  
  
sem_t smt;  
  
void DisplayData()  
{  
    printf ("Display a frame\n");  
}  
  
void *ThreadFuncDisplay(void *arg)  
{    
    printf("ThreadFuncDisplay thread start\n");
    while (1){  
        printf ("sem_wait..............................\n");  
        sem_wait (&smt);          
        DisplayData();        
    }  
}  
  
void *ThreadFuncControl(void *arg)  
{  
    printf("ThreadFuncControl thread start\n");
    while (1){  
        sleep (3);  
        sem_post (&smt);  
        printf ("sem_post\n");  
    }  
}  
  
int main(int argc, char *argv[])  
{  
    int rt;  
    pthread_t   pt_dsp;  
    pthread_t   pt_ctrl;  
      
  
    rt = sem_init (&smt, 0, 0);  
    if (rt){  
        perror ("semaphore initialization failed");  
    }  
  
    pthread_create (&pt_dsp, NULL, ThreadFuncDisplay, NULL);  
    pthread_create (&pt_ctrl, NULL, ThreadFuncControl, NULL);  
    
    pthread_join(pt_dsp, NULL);
    pthread_join(pt_ctrl, NULL);
    return 0;  
}  
