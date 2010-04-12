#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/processor.h>

static int hello_init(void)
{
	u32 data[4] = {0,0,0,0};
	struct cpuinfo_x86 *c = cpu_data + 0;
	cpuid(4, &data[0], &data[1], &data[2], &data[3] );

	printk(KERN_INFO "\nHello, world~~\n\n");
	printk(KERN_INFO "processor\t: 0\n"
                "vendor_id\t: %s\n"
                "cpu family\t: %d\n"
                "model\t\t: %d\n"
                "model name\t: %s\n"
		"x86_vendor\t: %d\n",
                c->x86_vendor_id[0] ? c->x86_vendor_id : "unknown",
                c->x86,
                c->x86_model,
                c->x86_model_id[0] ? c->x86_model_id : "unknown",
		c->x86_vendor);

	printk(KERN_INFO "a\t: %u\n"
		"b\t: %u\n"
		"c\t: %u\n"
		"d\t: %u\n",
		data[0], data[1], data[2], data[3]);

	return 0;
}

static void hello_exit(void)
{
	printk(KERN_INFO "\nGoodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Kong Wei<weikong@redflag-linux.com>");
MODULE_LICENSE("GPL");
