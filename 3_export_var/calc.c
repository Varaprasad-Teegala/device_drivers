#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include "header_calc.h"

int p,q;
module_param(p,int,0644);
module_param(q,int,0644);

int add(int a,int b)
{
	return a+b;
}

int sub(int a,int b)
{
	return a-b;
}

EXPORT_SYMBOL(add);
EXPORT_SYMBOL(sub);

static int modpar_init(void)
{
	printk("\nHello ! \n");
	printk("\t addition = %d\n",add(p,q));
	printk("\t subraction = %d\n",sub(p,q));
	printk("\t multiplication = %d\n",mul(p,q));
	printk("\t modulus = %d\n",modl(p,q));
	return 0;
}

static void modpar_exit(void)
{
	printk("\nThis is EXIT\n\n");
}

module_init(modpar_init);
module_exit(modpar_exit);

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("module parameters");

