/*
 * Init and load scull
 */
#include <linux/init.h>  // module_init, module_exit
#include <linux/module.h>
#include <linux/kdev_t.h>  // MKDEV 
#include <linux/fs.h>  // register_chrdev_region...
#include <linux/device.h>  // udev, class_create, class
#include <linux/cdev.h>  // cdev

#include "scull.h"


int scull_major = SCULL_MAJOR,
    scull_minor = SCULL_MINOR,
    scull_nr_devs = SCULL_NR_DEVS;

dev_t dev_num;
int result;
struct class *c_scull;
struct cdev dev_scull;


// file operations functions


static int scull_init(void) {
    printk(KERN_ALERT "scull init\n");
    // allocate dev_t ( the device number )
    if (scull_major) {  // static allocate 
        dev_num = MKDEV(scull_major, scull_minor);
        result = register_chrdev_region(dev_num, scull_nr_devs, "scull");
    } else {  // dynamic allocate
        result = alloc_chrdev_region(&dev_num, scull_minor, scull_nr_devs, "scull");
        scull_major = MAJOR(dev_num);
    }
    // check result
    if (result < 0) {  // fail to get major
        return -1;
    }

    // automatically create device file
    c_scull = class_create(THIS_MODULE, "scull");
    if (c_scull == NULL) {
        unregister_chrdev_region(dev_num, scull_nr_devs);
        return -1;
    }
    dev_scull = device_create(c_scull, NULL, dev_num, NULL, "scull");
    if (dev_scull == NULL) {
        class_destroy(c_scull);
        unregister_chrdev_region(dev_num, scull_nr_devs);
        return -1;
    }

    // TODO: Implementate file operation functions

    return 0;
}

static void scull_exit(void) {
    printk(KERN_ALERT "scull end\n");
    class_destroy(c_scull);
    unregister_chrdev_region(dev, scull_nr_devs);
}

module_init(scull_init);
module_exit(scull_exit);
