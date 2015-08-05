#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void) {
  printk(KERN_ALERT "Hello, world\n");
}

static int hello_exit(vodi) {
  printk(KERN_ALERT "bye\n");
}

module_init(hello_init);
module_exit(hello_exit);
