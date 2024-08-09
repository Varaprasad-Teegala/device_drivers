#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define my_WRITE _IOW('a','1',char *)
#define my_READ _IOR('a','2',char *)

int main()

{
	int fd = open("/dev/my_device_file",O_RDWR);
	char write_var[] = "Tea thaguthav entra?";
	char read_var[1024] ; 

	//printf("fd is : %d\n\nEnter a string : ",fd);
	//scanf("%[^\n]",read_var);
	
	printf("user to ioctl : %s\n",write_var);
        ioctl(fd,my_WRITE,(char *)write_var);

	//printf("Reading from ioctl......\n");
	ioctl(fd,my_READ,(char *)read_var);
	printf("ioctl to user = %s\n",read_var);

	close(fd);
}
