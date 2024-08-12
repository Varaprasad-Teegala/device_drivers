#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/ioctl.h>
#include<linux/proc_fs.h>
#include <linux/err.h>

MODULE_AUTHOR("PRASAD");
MODULE_LICENSE("GPLV2");
MODULE_DESCRIPTION("Device template");

//////////////////////////////////////////// FILE OPERATION ////////////////////////////////////////////////////

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
					.owner = THIS_MODULE,
					.open = my_open,
					.read = my_read,
					.write = my_write,
					.release = my_release,					
				 };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////// PROCFS ///////////////////////////////////////////////////////

char proc_buff[1024] = "I am process file system\n";
static struct proc_dir_entry *parent;

int my_proc_open (struct inode *inode, struct file *file)
{
	//printk("\nThis is procfs open\n File : %s\tFunction : %s\tLine:%d\n\n", __FILE__,__func__,__LINE__);
        pr_info("proc file opend......\n");
	return 0;
}

ssize_t my_proc_read (struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	pr_info("proc file read.......\n");
	int t = copy_to_user(buf,proc_buff,strlen(proc_buff));
	
	return 0;
}

ssize_t my_proc_write (struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	pr_info("proc file write.......\n");
	int t = copy_from_user(proc_buff,buf,lbuf);
	pr_info("from user : %s\n",proc_buff);
	*ppos += lbuf;
	return lbuf;
}

int my_proc_release (struct inode *inode, struct file *file)
{
	//printk("\nThis is procfs release\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
        pr_info("proc file closed........\n");
	return 0;
}

static struct proc_ops my_proc_fops = {
				      	.proc_open = my_proc_open,
					.proc_read = my_proc_read,
					.proc_write = my_proc_write,
					.proc_release = my_proc_release
				      };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int devfile_init(void)
{
	printk("\nThis is init\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	register_chrdev(60,"my_device_file",&dev_ops);

	parent = proc_mkdir("my_proc_dir",NULL);
	if(parent == NULL)
	{
		pr_info("Error in creating proc entry\n");
	}
	proc_create("my_proc_entry",0666,parent,&my_proc_fops);
	pr_info("Proc file of the device is created..\n");
	return 0;
}

static void devfile_exit(void)
{
	printk("\nThis is exit\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	unregister_chrdev(60,"my_device_file");
	proc_remove(parent);
	pr_info("Proc file of device is removed.....\n");
}

module_init(devfile_init);
module_exit(devfile_exit);

