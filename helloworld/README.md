# helloworld
## Things:
### Makefile
```
ifneq ($(KERNELRELEASE), )
	obj-m := hello.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
```
 - Value of `obj-m` must match the C file's name
   - How to manully point the C file?
    - `obj-m := your name`
 - `TODO`: add clean cods
   - Done

### gitignore
```
# my config
*.cmd
*.mod
.tmp_versions/
*.symvers
*.mod.c
*.order
```
### return types
```
static int **_init(void);
void **_exit(void);
```
