// from ldd3 p27
#include <linux/sched.h>

void print_current(void) {
    printk(KERN_ALERT "current is %s pid %i\n", current->comm, current->pid);
}
