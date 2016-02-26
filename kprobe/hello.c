#include <linux/init.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <asm/traps.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

//void print_current(void)
//void print_current(void) {
//    printk(KERN_ALERT "current is %s pid %i\n", current->comm, current->pid);
//}

struct kprobe my_kprobe;

int my_kprobe_handler (struct kprobe* kprobe_info, struct pt_regs* regs) {
	printk("Hi, I'm probing!\n");
	//dump_stack();
	//TODO: copy_from_user
	printk("thread %s - %d is trying to open %s", current->comm, current->pid, (char *) (regs->di));
	return 0;
}

static int hello_init(void) {
  printk(KERN_ALERT "Hello, world\n");
  //print_current();
  //printk(KERN_ALERT  "current is %s pid %i\n", current->comm, current->pid);
  memset(&my_kprobe, 0, sizeof(my_kprobe));
  my_kprobe.pre_handler = &my_kprobe_handler;
  my_kprobe.addr = ((void *) 0xffffffff8121d3e0);
  register_kprobe(&my_kprobe);
  return 0;
}

static void hello_exit(void) {
  unregister_kprobe(&my_kprobe);
  printk(KERN_ALERT "bye\n");
}

module_init(hello_init);
module_exit(hello_exit);
