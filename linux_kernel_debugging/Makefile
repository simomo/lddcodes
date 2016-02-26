#from linux kernel debug
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
obj-m := mine.o
default:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions \
			    Module.markers  modules.order  Module.symvers
