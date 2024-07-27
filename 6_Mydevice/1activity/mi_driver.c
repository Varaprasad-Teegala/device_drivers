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

#define MAJORNO 125
#define MINORNO  0
#define CHAR_DEV_NAME "psd_dev"
#define MAX_LENGTH 4096
#define SUCCESS 0
 
static char *char_device_buf;
struct cdev *vara_dev;
static char temp[1024];
dev_t mydev;
unsigned count = 0,inuse=0;
static struct class *vara_class;

int char_dev_open(struct inode *inode, struct file  *file)
{
	if(inuse)
	{
		printk(KERN_INFO "\nDevice busy %s\n",CHAR_DEV_NAME);
		return -EBUSY;
	}
	inuse=1;
	printk(KERN_INFO "Open operation invoked \n");
	return SUCCESS;
}
 
static int char_dev_release(struct inode *inode, struct file *file)
{
	inuse=0;
	printk(KERN_INFO "release operation invoked\n");
	return SUCCESS;
}

static ssize_t char_dev_write(struct file *file, const char *buf, size_t lbuf, loff_t *ppos)
{
	printk(KERN_INFO "write section ------->\n");
	//printk(KERN_INFO "Parameters :-\n\t*buf : %s\n\tlbuf : %ls\n\tppos : %d\n",buf,lbuf,(int) *ppos);
	int temlen = 0;
	int nbytes = 0;
	//memset(temp,'\0',1024);
	//*ppos = 0;
	if(count == 0)
	{
		if(temp[0] == '\0')
		{
        		nbytes = lbuf - copy_from_user (char_device_buf + *ppos, buf, lbuf);
        		*ppos += nbytes;
			count++;
		}
		else
		{
			nbytes = lbuf - copy_from_user (char_device_buf + *ppos, buf, lbuf);
                        *ppos += nbytes;
                        
			for(int i = 0 ; i<temlen ; i++)
                	{
                	        char_device_buf[*ppos + i] = temp[i];
                	        char_device_buf[*ppos + i + 1] = '\0';
                	}
                	*ppos += temlen;
		}
	}
	else if(count == 1)
	{
		temlen = lbuf - copy_from_user (temp, buf, lbuf);
		count--;
	}
	printk (KERN_INFO "\n Rec'vd data from user :  %s , nbytes : %d , *ppos : %d \n",char_device_buf,nbytes,(int)*ppos);
	printk(KERN_INFO "-------------------------------------------------------------------------\n");
	return nbytes;
}

static ssize_t char_dev_read(struct file *file, char *buf, size_t lbuf, loff_t *ppos)
{
 	printk(KERN_INFO "read section -------->\n");
	*ppos = 0;
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
	int ret;

	if (alloc_chrdev_region (&mydev, 0, count, CHAR_DEV_NAME) < 0)
        {  //1
            printk (KERN_ERR "failed to reserve major/minor range\n");
            return -1;
        }

        if (!(vara_dev = cdev_alloc ()))
        { //2
            printk (KERN_ERR "cdev_alloc() failed\n");
            unregister_chrdev_region (mydev, count);
            return -1;
        }

        cdev_init(vara_dev,&char_dev_fops);//3
					    
        ret=cdev_add(vara_dev,mydev,count);//4
        if( ret < 0 )
        {
                printk(KERN_INFO "Error registering device driver\n");
                cdev_del (vara_dev);
                unregister_chrdev_region (mydev, count);
        	return -1;
        }

        vara_class = class_create(THIS_MODULE->name);//5 extra
							   //
        device_create (vara_class, NULL, mydev, NULL, "%s", CHAR_DEV_NAME);//6 extra

        printk(KERN_INFO"\nDevice Registered: %s\n",CHAR_DEV_NAME);
        printk (KERN_INFO "Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));

        char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);

	memset(temp,'\0',1024);
	memset(char_device_buf,'\0',4096);

	return 0;
}
 
static void __exit char_dev_exit(void)
{ 
	cdev_del(vara_dev); //5
        class_destroy(vara_class);
	unregister_chrdev_region(mydev,1); //6
	kfree(char_device_buf);
	printk(KERN_INFO "\n Driver unregistered \n");
}
 
module_init(char_dev_init);
module_exit(char_dev_exit);
 
MODULE_AUTHOR("Varaprasad");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");
 
 
 
 
 
 
/* End of code */
 
#if 0
 
application layer fns(user space):
 
       1. int open(const char *pathname, int flags);
          int open(const char *pathname, int flags, mode_t mode);
 
       2. ssize_t read(int fd, void *buf, size_t count)
 
       3. ssize_t write(int fd, const void *buf, size_t count);
 
       4. int close(int fd);
 
==========================================================================================
VFS LAYER  "sree_cdrv"
==========================================================================================
 
driver fns(Kernel space)
========================================================================================
1. int (*open) (struct inode *, struct file *);
2. ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
3. ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
 
4. int (*release) (struct inode *, struct file *);
 
===========================================
 
 
Driver registration API's
==========================
 
1.register_chrdev_region()
2.cdev_alloc()
3.cdev_init()
4.cdev_add()
5. MKDEV()
 
6. copy_from_user()
7.copy_to_user()
 
++++++++++++++++<linux/uaccess.h>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
copy_from_user()
copy_to_user()
 
static __always_inline unsigned long __must_check
copy_from_user(void *to, const void __user *from, unsigned long n)
{
if (likely(check_copy_size(to, n, false)))
n = _copy_from_user(to, from, n);
return n;
}
 
static __always_inline unsigned long __must_check
copy_to_user(void __user *to, const void *from, unsigned long n)
{
if (likely(check_copy_size(from, n, true)))
n = _copy_to_user(to, from, n);
return n;
}
 
=====================================copy_from_user()==========================================
Name:
======
copy_from_user — Copy a block of data from user space.
 
Synopsis:
=========
unsigned long copy_from_user ( void *  to,
                          const void __user *  from,
                          unsigned long  n);
Arguments
==========
to
Destination address, in kernel space.
 
from
Source address, in user space.
 
n
Number of bytes to copy.
 
Description
==============
Copy data from user space to kernel space.
 
 
Return param:
=============
On failure, returns number of bytes that could not be copied. On success, this will be zero.
 
If some data could not be copied, this function will pad the copied data to the requested size using zero bytes.
 
===================================copy_to_user()==========================================================
Name
=====
copy_to_user — Copy a block of data into user space.
 
Synopsis:
=========
unsigned long copy_to_user ( void __user *  to,
  const void *  from,
  unsigned long  n);
Arguments:
===========
to
Destination address, in user space.
 
from
Source address, in kernel space.
 
n
Number of bytes to copy.
 
Description:
============
Copy data from kernel space to user space.
 
Returns number of bytes that could not be copied. On success, this will be zero.
 
 
 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <uapi/linux/kdev_t.h>
 
#define MINORBITS 20
#define MINORMASK ((1U << MINORBITS) - 1)
 
#define MAJOR(dev) ((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev) ((unsigned int) ((dev) & MINORMASK))
#define MKDEV(ma,mi) (((ma) << MINORBITS) | (mi))
 
 
/usr/src/linux-headers-4.15.0-39-generic/include/linux/fs.h:::
================================================================
1. extern int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *);
 
    alloc_chrdev_region — register a range of char device numbers
 
dev_t * dev
output parameter for first assigned number
 
unsigned baseminor
first of the requested range of minor numbers
 
unsigned count
the number of minor numbers required
 
const char * name
the name of the associated device or driver
 
 
2. extern int register_chrdev_region(dev_t, unsigned, const char *);
 
   register_chrdev_region — register a range of device numbers
 
dev_t from
the first in the desired range of device numbers; must include the major number.
 
unsigned count
the number of consecutive device numbers required
 
const char * name
the name of the device or driver.
 
3. void unregister_chrdev_region ( dev_t from,unsigned count);
 
    unregister_chrdev_region — unregister a range of device numbers
dev_t from
the first in the range of numbers to unregister
 
unsigned count
the number of device numbers to unregister
 
 
/usr/src/linux-headers-4.15.0-39-generic/include/linux/cdev.h:::
=================================================================
 
1. void cdev_init(struct cdev *, const struct file_operations *);
 
   cdev_init — initialize a cdev structure
 
2. struct cdev *cdev_alloc(void);
    
   cdev_alloc — allocate a cdev structure
   Allocates and returns a cdev structure, or NULL on failure.
 
3. void cdev_put(struct cdev *p);
 
4. int cdev_add(struct cdev *, dev_t, unsigned);
 
   cdev_add — add a char device to the system
 
struct cdev * p
the cdev structure for the device
 
dev_t dev
the first device number for which this device is responsible
 
unsigned count
the number of consecutive minor numbers corresponding to this device
   
5. void cdev_device_del(struct cdev *cdev, struct device *dev);
 
   cdev_del — remove a cdev from the system  
 
6. void cdev_set_parent(struct cdev *p, struct kobject *kobj);
 
 
7.  int cdev_device_add(struct cdev *cdev, struct device *dev);
 
 
8.  void cdev_del(struct cdev *);
    
    cdev_del — remove a cdev from the system
 
struct cdev * p
the cdev structure to be removed
 
 
steps to compile a driver
===========================
legacy driver
==============
1. make
2. mknod /dev/sree_cdrv c 300 0 //legacy way of compiling or assigning major/manor number
3. insmod chr_drv_skel.ko
4. gcc test_skel.c   (a.out)
5. ./a.out 
 
 
Advanced driver
===============
1. make
 
3. insmod chr_drv_skel.ko
4. gcc test_skel.c   (a.out)
5. ./a.out 
 
 
The major and minor numbers will be assigned dynamically in the driver program
 
init()
======
1. class_create()
2. device_create()
 
 
exit()
======
 
1. device_destroy()
2. class_destroy()
 
 
 
 
#endif
 
 
