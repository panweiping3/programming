/*
 * this is an kernel module to show how to use procfs.
 * /proc/asianux is to show the number of processes 
 * which are queued by process scheduler, 
 * and the number of processes for every priority.
 */
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>

#define ASIANUX_PROC_FILE_NAME "asianux"
#define ASIANUX_PROC_FILE_MODE 0444

// we use this array to store the number of processes for every priority.
static int prio_num[MAX_PRIO];

static void prio_num_init(void)
{
	int i;
	for (i=0; i<MAX_PRIO; ++i) {
		prio_num[i] = 0;	
	}
}

/*
 * When you 'cat /proc/asianux',
 * this function will be called.
 *
 * Note:
 * We donn't use any lock when using for_each_process() to traverse the task list,
 * so the process numbers of each priority is not accurate.
 * tasklist_lock isn't exported now, so it's not easy to lock the whole task list.
 */
static int asianux_proc_file_read(	char *page, 
									char **start, 
									off_t off,
									int count, 
									int *eof, 
									void *data)
{
	int i;
	int n = 0;
	int size = 0;
	int process_num = 0;
	char *p = NULL;
	struct task_struct *task_p = NULL;

	if (!page) {
		return -ENOMEM;
	}

	if (off > 0) {
		*eof = 1;	
		return 0;
	} else {
		prio_num_init();
		for_each_process(task_p) {
			prio_num[task_p->prio]++;
			process_num++;
		}

		p = page;
		for (i=0; i<MAX_PRIO; ++i) {
			n = sprintf(p, "priority[%d]:%d\n", i, prio_num[i]);
			size += n;
			p += n;
		}

		n = sprintf(p, "process number:%d\n", process_num);
		size += n;

		*eof = 1;	
	}

	return size;
}


static struct proc_dir_entry *asianux_proc = NULL;

int asianux_proc_module_init(void)
{
	int ret = 0;
	
	if (!asianux_proc) {
		// create /proc/asianux
		asianux_proc = create_proc_entry(ASIANUX_PROC_FILE_NAME, 
										ASIANUX_PROC_FILE_MODE, 
										NULL);
		if (!asianux_proc) {
			printk(KERN_ERR "Couldn't create proc entry\n");
			ret = -ENOMEM;
		} else {
			asianux_proc->read_proc = asianux_proc_file_read;
		}
	}

	return 0;
}

void asianux_proc_module_cleanup(void)
{
	remove_proc_entry(ASIANUX_PROC_FILE_NAME, NULL);

	return;
}

module_init(asianux_proc_module_init);
module_exit(asianux_proc_module_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pan Weiping panweiping3@163.com");
