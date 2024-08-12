sudo rmmod procfs_template
make clean
sudo dmesg -C
sudo make
sudo insmod procfs_template.ko
sudo dmesg
