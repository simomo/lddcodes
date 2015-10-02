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

static dev_t dev_num;
static int result;
static struct class *c_scull;
static struct cdev *dev_scull;


// file operations functions
static int scull_open(){}


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
    dev_scull = device_create(c_scull, NULL, dev_num, NULL, "scull");  // device_create will do alloc_dev's work, so we can call cdev_init directly 
    if (dev_scull == NULL) {
        class_destroy(c_scull);
        unregister_chrdev_region(dev_num, scull_nr_devs);
        return -1;
    }

    // init cdev structure, then add (register it to kernel)
    cdev_init(dev_scull, &scull_file_ops);
    if (cdev_add(dev_scull, dev_num, scull_nr_devs) == -1) {
        device_destroy(c_scull, dev_num);
        class_destroy(c_scull);
        unregister_chrdev_region(dev_num, scull_nr_devs);
        return -1;
    }



    return 0;
}

static void scull_exit(void) {
    printk(KERN_ALERT "scull end\n");
    // reverse cdev_add, cdev_init
    cdev_del(&dev_scull);
    // reverse device_create
    device_destroy(c_scull, dev_num);
    // reverse class_create
    class_destroy(c_scull);
    // reverse register_chrdev_region(static dev num) or alloc_chrdev_region(dynamic dev num)
    unregister_chrdev_region(dev_num, scull_nr_devs);
}

module_init(scull_init);
module_exit(scull_exit);
