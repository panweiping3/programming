obj-m   := module.o  
  
PWD := $(shell pwd)  
KERN_DIR = /lib/modules/$(shell uname -r)/build  
  
default:  
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules  
  
clean:  
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean  
