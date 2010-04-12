#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define LENGTH 256

extern char **environ;
pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen)
{
    int i, olen;
    int len = strlen(name);
    
    pthread_once(&init_done, thread_init);

    pthread_mutex_lock(&env_mutex);
    for (i = 0; environ[i] != NULL; ++i) {
        if (strncmp(environ[i], name, len) == 0) {
            if (strlen(environ[i]) > buflen) {
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strncpy(buf, environ[i], LENGTH);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }

    pthread_mutex_unlock(&env_mutex);
    return 1;
}

int main(int argc, char *argv[])
{
    char env[LENGTH];

    if (argc != 2) {
        fprintf(stderr, "./a.out aa\n");
        return 1;
    }
    
    getenv_r(argv[1], env, LENGTH);
    fprintf(stdout, "%s\n", env);

    return 0;
}
