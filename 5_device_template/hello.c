#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 

int l=0;
char s[1024];

int main()
{
	int fd = open("/dev/my_dev_driver",O_RDWR);
	if(fd < 0 )
	{
		perror("Cant open the char file\n");
		exit(0);
	}

	strcpy(s,"Mirafra");
	write(fd,s,strlen(s));
	l += strlen(s);

	strcpy(s,"Technologies");
        write(fd,s,strlen(s));
	l += strlen(s);

	strcpy(s,"Hightech city");
        write(fd,s,strlen(s));
        l += strlen(s);

	char x[l+1];
	read(fd,s,l);
	printf("from kernel to user : x = %s\n",s);
	close(fd);
}
