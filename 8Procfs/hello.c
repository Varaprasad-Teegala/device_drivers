#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 

int l=0;
char s[1024];

int main()
{
	int fd = open("/proc/my_proc_dir/my_proc_entry",O_RDWR);
	if(fd < 0 )
	{
		perror("Cant open the char file\n");
		exit(0);
	}

	read(fd,s,100);
        printf("from kernel to user : x = %s\n",s);

	strcpy(s,"Hello how r u?");
	write(fd,s,strlen(s));
	
	close(fd);
}
