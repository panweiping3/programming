ifneq ($(KERNELRELEASE),)
	obj-m := kernel_mod.o  

# Otherwise we were called directly from the command
# # line; invoke the kernel build system.
#
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	rm kernel_mod.mod.c kernel_mod.mod.o kernel_mod.o Module.markers modules.order Module.symvers -rf
