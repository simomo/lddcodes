/*
 * Init and load scull
 */
#include <linux/init.h>  // module_init, module_exit
#include <linux/module.h>
#include <linux/kdev_t.h>  // MKDEV 
#include <linux/fs.h>  // register_chrdev_region...
#include <linux/device.h>  // class_create, class

#include "scull.h"


int scull_major = SCULL_MAJOR,
    scull_minor = SCULL_MINOR,
    scull_nr_devs = SCULL_NR_DEVS;

dev_t dev;
int result;

static int scull_init(void) {
    printk(KERN_ALERT "scull init\n");
    // allocate dev_t ( the device number )
    if (scull_major) {  // static allocate 
        dev = MKDEV(scull_major, scull_minor);
        result = register_chrdev_region(dev, scull_nr_devs, "scull");
    } else {
        result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
        scull_major = MAJOR(dev);
    }
    // check result
    if (result < 0) {  // fail, no needs to do unregister, since register operation not succeed.
        // unregister_chrdev_region(dev, scull_nr_devs);
        return -1;
    }

    // create the device files (under /dev ), using the udev daemon

    return 0;
}

static void scull_exit(void) {
    printk(KERN_ALERT "scull end\n");
    unregister_chrdev_region(dev, scull_nr_devs);
}

module_init(scull_init);
module_exit(scull_exit);
