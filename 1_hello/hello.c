#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

static int hello_init(void)
{
	printk("Hello ! this is my first module and its INIT\n");
	return 0;
}

static void hello_exit(void)
{
	printk("This is EXIT\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPL");

