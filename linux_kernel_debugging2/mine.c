#include <linux/module.h>
#include <linux/timer.h>


MODULE_LICENSE("GPL");

int sec_delay = 15;

module_param(sec_delay, int, 0);
struct timer_list my_timer;

void my_timer_func (unsigned long arg) {
	printk("in timer, arg was: %x and jiffies is %d\n", arg, jiffies);
}

static int __init my_module_entry(void) {
	printk("jiffies is %d\n", jiffies);
	my_timer.function = my_timer_func;
	my_timer.data = (void *) 0x10241975;
	my_timer.expires = jiffies + (sec_delay * HZ);

	add_timer(&my_timer);
	return (0);
}


static void __exit my_module_exit(void) {
	printk("bye\n");
}


module_init(my_module_entry);
module_exit(my_module_exit);
