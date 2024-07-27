sudo rmmod mi_driver
sudo dmesg -C
make clean
clear
make
sudo insmod mi_driver.ko
