sudo rmmod dev_template
make clean
sudo dmesg -C
sudo make
sudo insmod dev_template.ko
sudo dmesg
