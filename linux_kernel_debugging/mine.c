#include <linux/module.h>
#include <linux/notifier.h>
#include <linux/inetdevice.h>

MODULE_LICENSE("GPL");




int my_callback(struct notifier_block *self,
		unsigned long event,
		void *arg) {
	printk("event: %ld, arg: %p\n", event, arg);
	return (NOTIFY_DONE);
}


static int __init my_module_entry (void) {
struct notifier_block my_notifier;
	my_notifier.next = NULL;
	my_notifier.priority = 10;
	my_notifier.notifier_call = my_callback;

	register_inetaddr_notifier(&my_notifier);
	printk("hello\n");

	return (0);
}


static void __exit my_module_exit(void) {
	printk("bye\n");
}


module_init(my_module_entry);
module_exit(my_module_exit);
