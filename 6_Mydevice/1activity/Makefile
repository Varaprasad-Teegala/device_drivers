#obj-m :=my_driver.o
#obj-m :=driver.o
 
#obj-m :=sree-driver.o
 
#obj-m :=driver_dynamic.o
#obj-m += char_driver_dynamic.o
 
 
#obj-m += chr_drv_dynamic.c
 
 
 
#KDIR= /lib/modules/$(shell uname -r)/build
 
#all:
	#$(MAKE) -C $(KDIR) M=$(shell pwd) modules
 
#clean:
	#rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c )


obj-m := mi_driver.o

all :
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
clean :
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
install :
	make -C /lib/modules/`uname -r`/build M=`pwd` modules_install
