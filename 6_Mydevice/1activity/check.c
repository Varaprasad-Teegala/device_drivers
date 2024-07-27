#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>

char s[1024] ;
int l=0;

int main()
{
	int fd = open("/dev/psd_dev",O_RDWR);
	if(fd < 0 )
	{
		perror("Cant open the char file\n");
		exit(0);
	}

	strcpy(s,"Mirafra ");
	write(fd,s,strlen(s));
	l += strlen(s);

	strcpy(s,"Technologies ");
        write(fd,s,strlen(s));
	l += strlen(s);

	strcpy(s,"Hyderabad");
        write(fd,s,strlen(s));
        l += strlen(s);

	char x[l+1];
	read(fd,x,l);
	printf("from kernel to user : x = %s\n",x);
	close(fd);
}

