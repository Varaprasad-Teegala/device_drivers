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

int l=0;
char s[1024];

int main()
{
	int fd = open("/dev/reverse",O_RDWR);
	if(fd < 0 )
	{
		perror("Cant open the char file\n");
		exit(0);
	}
	
	write(fd,"hello kernel",13);
	read(fd,s,1024);
	printf("reversed string : %s\n",s);
	close(fd);
	return 0;
}
