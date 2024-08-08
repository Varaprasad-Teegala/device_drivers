sudo rmmod my_code
sudo dmesg -C
make clean
clear
make
sudo insmod my_code.ko
