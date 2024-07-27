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
static char temp[1024];
unsigned count = 0;
int temlen = 0;
int nbytes = 0;

int my_open(struct inode *inode , struct file *file)
{
	printk("\nThis is open------------------------------------->\n File : %s\tFunction : %s\tLine:%d\n\n", __FILE__,__func__,__LINE__);
	return 0;
}

ssize_t my_read (struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	
	*ppos = 0;
        int nbytes = lbuf - copy_to_user (buf, char_device_buf + *ppos, lbuf);
        *ppos += nbytes;
        printk (KERN_INFO "\n Reading nbytes=%d, pos=%d \n",nbytes, (int)*ppos);
 	
	return 0;
}

ssize_t my_write (struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{

        if(count == 0)
        {
                if(temp[0] == '\0')
                {
                        nbytes = lbuf - copy_from_user (char_device_buf + *ppos, buf, lbuf);
                        *ppos += nbytes;
                        count++;
			printk("resp 1\n");
                }
                else
                {
			printk("resp 3\n");
                        nbytes = lbuf - copy_from_user (char_device_buf + *ppos, buf, lbuf);
                        *ppos += nbytes;
			//printk("\n\nchar_device_buf = %s ppos : %d\n\n\n",char_device_buf,(int) *ppos);
			printk (KERN_INFO "\n Rec'vd data from user :  %s , nbytes : %d , *ppos : %d   temp : %s   temlen : %d\n",char_device_buf,nbytes,(int)*ppos,temp,temlen);

                        for(int i = 0 ; i<temlen ; i++)
                        {
				printk("resp4");
                                char_device_buf[*ppos + i] = temp[i];
                                char_device_buf[*ppos + i + 1] = '\0';
				printk("char_device_buf[%llu] = %c\n",*ppos + i,char_device_buf[*ppos + i]);
                        }
                        *ppos += temlen;
                }
        }
	else if(count == 1)
        {
		printk("resp 2\n");
                temlen = lbuf - copy_from_user (temp, buf, lbuf);
                count--;
        }
        printk (KERN_INFO "\n Rec'vd data from user :  %s , nbytes : %d , *ppos : %d   temp : %s   temlen : %d\n",char_device_buf,nbytes,(int)*ppos,temp,temlen);
	//printk("-------------------------------------------------------------------------\n");
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
	register_chrdev(60,"my_dev_driver",&dev_ops);
	char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);

        memset(temp,'\0',1024);
        memset(char_device_buf,'\0',4096);

	return 0;
}

static void devfile_exit(void)
{
	printk("\nThis is exit\nFile : %s\tFunction : %s\tLine:%d\n",__FILE__,__func__,__LINE__);
	unregister_chrdev(60,"my_dev_driver");
	kfree(char_device_buf);
	printk("Device is unregistered\n");
}

module_init(devfile_init);
module_exit(devfile_exit);

