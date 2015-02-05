//Chris Park CSCD340

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAX 1000
int main()
{
	int fd[2];
	
	if(pipe(fd) < 0)
	{
		printf("Failure.");
		exit(0);
	}
	
	if(fork() == 0)
	{
		close(fd[0]);
		close(1);
		dup(fd[1]);
		close(fd[1]);
		
		execlp("ls", "ls", "-al", NULL);

	}
	else
	{
		close(fd[1]);
		close(0);
		dup(fd[0]);
		
		execlp("wc", "wc", "-w", NULL);	
	}
}
