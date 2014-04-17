obj-m := netlink_k.o
KERNELBUILD := /lib/modules/`uname -r`/build
default:
	@echo "BUILE Kmod"
	@make -C $(KERNELBUILD) M=$(shell pwd) modules
	gcc -o netlink_u netlink_u.c
clean:
	@echo " CLEAN kmod"
	@rm -rf *.o netlink_u
	@rm -rf .depend *.order .*.cmd *.ko *.mod.c .tmp_versions *.symvers .*.d 
