#include <linux/init.h>  
#include <linux/module.h>  
MODULE_LICENSE("GPL");  

static __init int simple_module_init(void)  
{  
    printk(KERN_ALERT "module init!/n");  
    return 0;  
}  
  
static __exit void simple_module_exit(void)  
{  
    printk(KERN_ALERT "module exit!/n");  
}  
  
module_init(simple_module_init);  
module_exit(simple_module_exit);
