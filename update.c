#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include"make_log.h"

int main(int argc, char* argv[])
{
	int fd[2];
	int fp;
	int ret = pipe(fd);
	char buf[1024] = {0};
	if(ret == -1)
	{
		perror("pipe");
		exit(1);
	}

		pid_t pid = fork();
		if(pid == 0)
		{
			close(fd[0]);
			fp = dup2(fd[1],STDOUT_FILENO);
			if(fp == -1){
				perror("dup2");
				exit(1);
			}
			execlp("fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf",argv[1],NULL);
			if(ret == -1){
				perror("execlp");
				exit(1);
			}
		}
		else if(pid > 0)
		{
			close(fd[1]);
			wait(NULL);
			read(fd[0],buf,sizeof(buf));
			LOG("test","fdfs", "buf=[%s]", buf);
		}
		return 0;
		
}
