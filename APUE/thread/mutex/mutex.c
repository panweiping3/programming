#include "foo.h"

struct foo *g_foo_p = NULL;

void *hold_thread(void *arg)
{
    int r = 0;
    while (1) {
        r = rand() % 5;
        sleep(r);
        if (r % 2 == 0) {
            if (g_foo_p) {
                foo_hold(g_foo_p);
                fprintf(stderr, "count +1\n");
                foo_read(g_foo_p);
            } else {
                pthread_exit(NULL);
            }
        }
    }
}

void *release_thread(void *arg)
{
    int r = 0;
    while (1) {
        r = rand() % 5;
        sleep(r);
        if (r % 3 == 0) {
            if (g_foo_p) {
                if (foo_rele(g_foo_p) == 1) {
                    g_foo_p = NULL;
                } else {
                    fprintf(stderr, "count -1\n");
                    foo_read(g_foo_p);
                }
            } else {
                pthread_exit(NULL);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t tid1, tid2;

    g_foo_p = foo_alloc(); 
    if (!g_foo_p) {
        exit(1);
    }
    
    foo_read(g_foo_p);
 
    err = pthread_create(&tid1, NULL, hold_thread, NULL);
    if (err != 0) {
        exit(2);
    }

    err = pthread_create(&tid2, NULL, release_thread, NULL);
    if (err != 0) {
        exit(3);
    }

    err = pthread_join(tid1, NULL);
    if (err != 0) {
        exit(4);
    }
    err = pthread_join(tid2, NULL);
    if (err != 0) {
        exit(5);
    }

    return 0;
}
