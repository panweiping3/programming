#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Kong Wei<weikong@redflag-linux.com>");
MODULE_LICENSE("GPL");

static int hello_init(void)
{
	printk(KERN_ERR "Hello, world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ERR "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
