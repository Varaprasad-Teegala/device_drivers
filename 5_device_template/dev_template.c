#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("Device template");

int my_open(struct inode *,struct file *)
{
	printk("\nThis is open\n File : %s\tFunction : %s\tLine:%d\n\n", __FILE__,__func__,__LINE__);
	return 0;
}

ssize_t my_read (struct file *, char __user *, size_t, loff_t *)
{
	printk("\nThis is read\n File : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	return 0;
}

ssize_t my_write (struct file *, const char __user *, size_t, loff_t *)
{
	printk("\nThis is write\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	return 0;
}

int my_release(struct inode *,struct file *)
{
	printk("\nThis is release\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	return 0;
}

struct file_operations dev_ops = {
					.open = my_open,
					.read = my_read,
					.write = my_write,
					.release = my_release,					
				 };

static int devfile_init(void)
{
	printk("\nThis is init\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	register_chrdev(60,"my_device_file",&dev_ops);
	return 0;
}

static void devfile_exit(void)
{
	printk("\nThis is exit\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	unregister_chrdev(60,"my_device_file");
}

module_init(devfile_init);
module_exit(devfile_exit);

