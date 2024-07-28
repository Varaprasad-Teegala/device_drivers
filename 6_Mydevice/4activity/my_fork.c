#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

#define MAX_LENGTH 4096

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("Device template");

static char *char_device_buf;
int nbytes = 0;
int t;

int my_open(struct inode *inode , struct file *file)
{
	printk("\nThis is open------------------------------------->\n File : %s\tFunction : %s\tLine:%d\n\n", __FILE__,__func__,__LINE__);
	return 0;
}

ssize_t my_read (struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	if(char_device_buf[0] == '\0')
		t = copy_to_user (buf,"kernel Buffer is empty",23);
	else
	{
		*ppos = 0;
        	int nbytes = lbuf - copy_to_user (buf, char_device_buf + *ppos, lbuf);
        	*ppos += nbytes;
        	printk (KERN_INFO "\n Reading nbytes=%d, pos=%d \n",nbytes, (int)*ppos);
		memset(char_device_buf,'\0',*ppos);
		*ppos = 0;
	}
	return 0;
}

ssize_t my_write (struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	nbytes = lbuf - copy_from_user (char_device_buf + *ppos, buf, lbuf);
        *ppos += nbytes;
        printk (KERN_INFO "\n Rec'vd data from user :  %s , nbytes : %d , *ppos : %d  \n",char_device_buf,nbytes,(int)*ppos);
	return 0;
}

int my_release(struct inode *inode,struct file *file)
{
	printk("\nThis is release---------------------------------->\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
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
	register_chrdev(60,"my_fork",&dev_ops);
	char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);

        memset(char_device_buf,'\0',4096);

	return 0;
}

static void devfile_exit(void)
{
	printk("\nThis is exit\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	unregister_chrdev(60,"my_fork");
	kfree(char_device_buf);
	printk("Device is unregistered\n");
}

module_init(devfile_init);
module_exit(devfile_exit);

