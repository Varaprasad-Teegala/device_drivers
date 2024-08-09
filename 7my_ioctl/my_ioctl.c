#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("Device template");

//int32_t kernel_buf = 0;
int t = 0;
char * kernel_buf;

// #define my_WRITE _IOR('a','b',int32_t *)		/////
// #define my_READ _IOW('a','a',int32_t *)		////
#define my_WRITE _IOW('a','1',char *)
#define my_READ _IOR('a','2',char *)

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

//long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
long my_ioctl(struct file * file, unsigned int cmd, unsigned long arg)			//////
{
	switch(cmd)
	{
		case my_READ:	strcpy(kernel_buf,"Naku tea elavatu ledu andi...");
				t = copy_to_user((char *)arg, kernel_buf ,strlen(kernel_buf));
				printk("This is READ in ioctl : kernel_buf = %s\n",kernel_buf);
				memset(kernel_buf,'\0',1024);	
				break;

		case my_WRITE:	t = copy_from_user(kernel_buf,(char *)arg, 1024);
				printk("This is WRITE in ioctl : kernel_buf = %s \n",kernel_buf);
				memset(kernel_buf,'\0',1024);
				break;

		default : printk("This is default\n");
			  break;
	}
	return 0;
}

struct file_operations dev_ops = {
					.owner = THIS_MODULE,
					.open = my_open,
					.read = my_read,
					.write = my_write,
					.unlocked_ioctl = my_ioctl,                /////
					.release = my_release,					
				 };

static int devfile_init(void)
{
	printk("\nThis is init\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	register_chrdev(60,"my_device_file",&dev_ops);
	kernel_buf  = (char *)kmalloc(1024,GFP_KERNEL);
	memset(kernel_buf,'\0',1024);
	return 0;
}

static void devfile_exit(void)
{
	printk("\nThis is exit\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	unregister_chrdev(60,"my_device_file");
	kfree(kernel_buf);
}

module_init(devfile_init);
module_exit(devfile_exit);

