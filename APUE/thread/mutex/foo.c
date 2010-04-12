#include "foo.h"

struct foo * foo_alloc(void)
{
    struct foo *fp = NULL;

    if ((fp = malloc(sizeof(struct foo))) != NULL) {
        fp->f_count = 1;
        if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
            free(fp);
            return NULL;
        }
    }
    
    return fp;
}

void foo_hold(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

int foo_rele(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0) {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
        return 1;
    } else {
        pthread_mutex_unlock(&fp->f_lock);
    }

    return 0;
}

void foo_read(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fprintf(stderr, "count %d\n", fp->f_count);
    pthread_mutex_unlock(&fp->f_lock);
}
