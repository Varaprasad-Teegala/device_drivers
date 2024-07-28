sudo rmmod kernel_reverse
make clean
sudo dmesg -C
sudo make
sudo insmod kernel_reverse.ko
sudo dmesg
