/*
 * this is an kernel module to show how to use sysfs.
 * /sys/asianux/process_numbers is to show 
 * the number of processes which are queued by process scheduler.
 * /sys/asianux/priority_numbers is to show 
 * the number of processes for every priority.
 */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

#define ASIANUX_SYSFS_DIR_NAME "asianux"
#define ASIANUX_SYSFS_PRIORITY_FILE_NAME priority_numbers
#define ASIANUX_SYSFS_PROCESS_FILE_NAME process_numbers
#define ASIANUX_SYSFS_PRIORITY_FILE_MODE 0444
#define ASIANUX_SYSFS_PROCESS_FILE_MODE 0444

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
 * When you 'cat /sys/asianux/priority_numbers',
 * this function will be called.
 *
 * Note:
 * We donn't use any lock when using for_each_process() to traverse the task list,
 * so the process numbers of each priority is not accurate.
 * tasklist_lock isn't exported now, so it's not easy to lock the whole task list.
 */

static ssize_t prio_show(struct kobject *kobj, struct kobj_attribute *attr,
						 char *buf)
{
	int i;
	ssize_t size = 0;
	int n = 0;
	char *p = buf;
	struct task_struct *task_p = NULL;

	if (!p) {
		return 0;
	}

	prio_num_init();
	for_each_process(task_p) {
		prio_num[task_p->prio]++;
	}

	for (i=0; i<MAX_PRIO; ++i) {
		n = sprintf(p, "priority[%d]:%d\n", i, prio_num[i]);
		size += n;
		p += n;
	}

	return size;
}

/* 
 * When you 'cat /sys/asianux/process_numbers',
 * this function will be called.
 *
 * Note:
 * We donn't use any lock when using for_each_process() to traverse the task list,
 * so the process numbers of each priority is not accurate.
 * tasklist_lock isn't exported now, so it's not easy to lock the whole task list.
 */
static ssize_t num_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	int num = 0;
	struct task_struct *task_p = NULL;

	if (!buf) {
		return -ENOMEM;
	}

	for_each_process(task_p) {
		num++;
	}

	return sprintf(buf, "process number:%d\n", num);
}

static struct kobj_attribute prio_attribute =
	__ATTR(	ASIANUX_SYSFS_PRIORITY_FILE_NAME, 
			ASIANUX_SYSFS_PRIORITY_FILE_MODE, 
			prio_show, 
			NULL);

static struct kobj_attribute num_attribute =
	__ATTR(	ASIANUX_SYSFS_PROCESS_FILE_NAME, 
			ASIANUX_SYSFS_PROCESS_FILE_MODE, 
			num_show, 
			NULL);

static struct attribute *attrs[] = {
	&prio_attribute.attr,
	&num_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *asianux_kobj = NULL;

static int asianux_sysfs_init(void)
{
	int retval;
	
	// create an entry is /sys/
	asianux_kobj = kobject_create_and_add(ASIANUX_SYSFS_DIR_NAME, NULL);
	if (!asianux_kobj)
		return -ENOMEM;

	// create an attribute group with attr_group
	retval = sysfs_create_group(asianux_kobj, &attr_group);
	if (retval)
		kobject_put(asianux_kobj);

	return retval;
}

static void asianux_sysfs_exit(void)
{
	// decrease the reference of asianux_kobj.
	// if the reference of asianux_kobj is 0, 
	// it will be deleted automatically.
	kobject_put(asianux_kobj);
}

module_init(asianux_sysfs_init);
module_exit(asianux_sysfs_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pan Weiping panweiping3@163.com");
