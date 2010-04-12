#ifndef FOO_H
#define FOO_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct foo {
    int f_count;
    pthread_mutex_t f_lock;
};

struct foo * foo_alloc(void);
void foo_hold(struct foo *fp);
int foo_rele(struct foo *fp);
void foo_read(struct foo *fp);

#endif
