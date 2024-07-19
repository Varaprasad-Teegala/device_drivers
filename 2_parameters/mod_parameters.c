#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

int p;
module_param(p,int,0644);

static int modpar_init(void)
{
	printk("\nHello ! this is module parameters and p=%d\n\n",p);
	return 0;
}

static void modpar_exit(void)
{
	printk("\nThis is EXIT and p=%d\n\n",p);
}

module_init(modpar_init);
module_exit(modpar_exit);

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("module parameters");

