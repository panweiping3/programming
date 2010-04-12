#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <pthread.h>

static pthread_key_t g_data_key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void free_key(void *arg)
{
    fprintf(stderr, "%s %d %s pthread_key_delete\n", __FILE__, __LINE__, __func__);     
    pthread_key_delete(g_data_key);
}

static void thread_init(void)
{
    fprintf(stderr, "%s %d %s %u\n", __FILE__, __LINE__, __func__, g_data_key);     
    pthread_key_create(&g_data_key, free_key);
    fprintf(stderr, "%s %d %s %u\n", __FILE__, __LINE__, __func__, g_data_key);     
}

char *getenv(const char *name)
{
    int i, len;
    char *envbuf;

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = (char *)pthread_getspecific(g_data_key);
    if (envbuf == NULL) {
        envbuf = malloc(ARG_MAX);
        if (envbuf == NULL) {
            pthread_mutex_unlock(&env_mutex);
            return NULL;
        }
        pthread_setspecific(g_data_key, envbuf);
    }

    len = strlen(name);

    for (i = 0; environ[i] != NULL; ++i) {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
            strcpy(envbuf, &environ[i][len + 1]);
            pthread_mutex_unlock(&env_mutex);
            return envbuf;
        }
    }

    pthread_mutex_unlock(&env_mutex);
    return NULL;
}

void *thread1(void *arg)
{
    char *p = (char *)arg;
    fprintf(stdout, "%s=%s\n", p, getenv(p));
    return NULL;
}

void *thread2(void *arg)
{
    char *p = (char *)arg;
    fprintf(stdout, "%s=%s\n", p, getenv(p));
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    if (argc != 2) {
        fprintf(stderr, "./a.out aa\n");
        return 1;
    }
    
    pthread_create(&tid, NULL, thread1, argv[1]);
    pthread_create(&tid, NULL, thread2, argv[1]);

    return 0;
}
