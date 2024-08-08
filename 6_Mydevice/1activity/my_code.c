#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/device.h>

#define MAX_LENGTH 4096
#define SUCCESS 0
 
static char *char_device_buf;

int char_dev_open(struct inode *inode, struct file  *file)
{
	
	printk(KERN_INFO "Open operation invoked \n");
	return SUCCESS;
}
 
static int char_dev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "release operation invoked\n");
	return SUCCESS;
}

static ssize_t char_dev_write(struct file *file, const char *buf, size_t lbuf, loff_t *ppos)
{
	printk(KERN_INFO "write section ------->\n");
	printk(KERN_INFO "Parameters :-\n\t*buf : %s\n\tlbuf : %lld\n\tppos : %d\n",buf,lbuf,(int) *ppos);
	int nbytes = 0;
	
	nbytes = lbuf - copy_from_user (char_device_buf + *ppos, buf, lbuf);
        *ppos += nbytes;

	printk (KERN_INFO "\n Rec'vd data from user :  %s , nbytes : %d , *ppos : %d \n",char_device_buf,nbytes,(int)*ppos);
	printk(KERN_INFO "-------------------------------------------------------------------------\n");
	return nbytes;
}

static ssize_t char_dev_read(struct file *file, char *buf, size_t lbuf, loff_t *ppos)
{
 	printk(KERN_INFO "read section -------->\n");
	*ppos = 0;
	printk(KERN_INFO "Parameters :-\n\t*buf : %s\n\tlbuf : %lld\n\tppos : %d\n",buf,lbuf,(int) *ppos);
       	int nbytes = lbuf - copy_to_user (buf, char_device_buf + *ppos, lbuf);
       	*ppos += nbytes; 
       	printk (KERN_INFO "\n Reading nbytes=%d, pos=%d \n",nbytes, (int)*ppos); 
	printk("-------------------------------------------------------------------------\n");
	return 0;
}
 
static struct file_operations char_dev_fops = 
{
	.owner = THIS_MODULE,
	.write = char_dev_write,
	.read = char_dev_read,
	.open = char_dev_open,
	.release = char_dev_release
};
 
static int __init char_dev_init(void)
{
	register_chrdev(60,"my_print",&char_dev_fops);
	char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);
        memset(char_device_buf,'\0',4000);

	return 0;
}
 
static void __exit char_dev_exit(void)
{
	unregister_chrdev(60,"my_print");
	kfree(char_device_buf);
	printk("Device is unregistered\n");
}
 
module_init(char_dev_init);
module_exit(char_dev_exit);
 
MODULE_AUTHOR("Varaprasad");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

