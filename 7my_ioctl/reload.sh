clear
sudo rmmod my_ioctl
make clean
sudo dmesg -C
sudo make
sudo insmod my_ioctl.ko
sudo dmesg
