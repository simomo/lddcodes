#include <linux/init.h>
#include <linux/module.h>

void print_current(void)

static int hello_init(void) {
  printk(KERN_ALERT "Hello, world\n");
  print_current();
  //printk(KERN_ALERT  "current is %s pid %i\n", current->comm, current->pid);
  return 0;
}

static void hello_exit(void) {
  printk(KERN_ALERT "bye\n");
}

module_init(hello_init);
module_exit(hello_exit);
