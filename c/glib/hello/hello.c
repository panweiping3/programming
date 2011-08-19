#include <stdio.h>
#include <glib.h>
static GMutex *mutex = NULL;
static gboolean t1_end = FALSE;
static gboolean t2_end = FALSE;
typedef struct _Arg Arg;
struct _Arg
{
	GMainLoop* loop;
	gint max;
};

gpointer run_1(gpointer *arg)
{
	int i ;
	
	for(i=0; i<((Arg *)arg)->max; i++) {
		if(g_mutex_trylock(mutex) == FALSE) {
			g_print("%d : thread 2 locked the mutex \n", i);
			g_mutex_unlock(mutex);
		} else {
			g_usleep(10);
		}
	}
	t1_end = TRUE;
}

gpointer run_2(gpointer *arg)
{
	int i;
	for(i=0; i<((Arg *)arg)->max; i++) {
		if(g_mutex_trylock(mutex) == FALSE) {
			g_print("%d : thread 1 locked mutex \n", i);
			g_mutex_unlock(mutex);
		} else {
			g_usleep(10);
		}
	}
	t2_end = TRUE;
}

gpointer run_3(gpointer *arg)
{
	for(;;) {
		if(t1_end && t2_end) {
			g_main_loop_quit(((Arg *)arg)->loop);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	GMainLoop *mloop;
	Arg *arg;
	GThreadFunc func;
	
	if(!g_thread_supported())
		g_thread_init(NULL);
	mloop = g_main_loop_new(NULL, FALSE);
	
	arg = g_new(Arg, 1);
	arg->loop = mloop;
	arg->max = 11;
		
	mutex = g_mutex_new();
	func = (GThreadFunc)run_1;
	g_thread_create(func, arg, TRUE, NULL);
	func = (GThreadFunc)run_2;
	g_thread_create(func, arg, TRUE, NULL);
	func = (GThreadFunc)run_3;
	g_thread_create(func, arg, TRUE, NULL);
	
	g_main_loop_run(mloop);
	g_print("thread3 exit event loop\n");
	g_mutex_free(mutex);
	g_print("release mutex\n"); 
	g_free(arg);
	g_print("free memory\n");
	fprintf(stderr, "%s %d %s 潘卫平\n", __FILE__, __LINE__, __func__);	
}

