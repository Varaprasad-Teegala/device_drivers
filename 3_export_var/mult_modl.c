#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("module parameters");

int mul(int a,int b)
{
	return a*b;
}

int modl(int a,int b)
{
	return a%b;
}

EXPORT_SYMBOL(mul);
EXPORT_SYMBOL(modl);

static int arthm_init(void)
{
	return 0;
}

static void arthm_exit(void)
{

}

module_init(arthm_init);
module_exit(arthm_exit);


