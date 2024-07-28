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
char s[3072];

int main()
{
	int fd = open("/dev/2kbyte",O_RDWR);
	int txt = open("text.txt",O_RDWR);
	if(fd < 0 )
	{
		perror("Cant open the char file\n");
		exit(0);
	}
	if(txt < 0 )
        {
                perror("Cant open the text file\n");
                exit(0);
        }

	int t;
	char c;
	lseek(fd,0,SEEK_SET);
	do
	{
		t = read(txt,&c,1);
		write(fd,&c,1);	
	}
	while(t);

	read(fd,s,3072);
	printf("length of kernel string : %ld\n",strlen(s));

	close(fd);
	close(txt);
	return 0;
}
