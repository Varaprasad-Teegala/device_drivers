sudo rmmod my_fork
make clean
sudo dmesg -C
sudo make
sudo insmod my_fork.ko
sudo dmesg
