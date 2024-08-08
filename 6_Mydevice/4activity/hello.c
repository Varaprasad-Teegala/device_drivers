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
	int fd = open("/dev/my_print",O_RDWR);
	if(fd < 0 )
	{
		perror("Cant open the char file\n");
		exit(0);
	}

	//pid_t x = fork();

	while(1)
	{
		int status;
		memset(s,'\0',sizeof(s));
		pid_t x = fork();
		if (x == 0) // child process
		{
			printf("Child process------------>\n");
			printf("Enter an option \n\t1) Read from kernel\n\t2) Write to kernel\n");
			int c;
			scanf("%d",&c);
			getchar();
			if(c == 1) // Read
			{
				read(fd,s,1024);
				printf("From kernel : %s\n",s);
				memset(s,'\0',sizeof(s));
			}
			else if (c == 2)// write
			{
				printf("To kernel : ");
				scanf("%[^\n]",s);
				getchar();
				write(fd,s,strlen(s));
				memset(s,'\0',sizeof(s));
			}
			else
				printf("Invalid \n");
			exit(0);		
		}
		else if (x > 0) // Parent process
		{
			wait(&status);
			printf("Parent process------------>\n");
                        printf("Enter an option \n\t1) Read from kernel\n\t2) Write to kernel\n");
                        int c;
                        scanf("%d",&c);
			getchar();
                        if(c == 1) // Read
                        {
                                read(fd,s,1024);
                                printf("From kernel : %s\n",s);
                                memset(s,'\0',sizeof(s));
                        }
                        else if (c == 2)// write
                        {
                                printf("To kernel : ");
                                scanf("%[^\n]",s);
                                getchar();
                                write(fd,s,strlen(s));
                                memset(s,'\0',sizeof(s));
                        }
                        else
                                printf("Invalid \n");
		}

		else
		{
			perror("Fork failed\n");
			exit(0);
		}
	}

	close(fd);
	return 0;
}
