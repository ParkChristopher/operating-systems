//Chris Park

#include "shellRoutines.h"

void forkIt(Arg *arguments, LinkedList *histList, LinkedList *aliasList)
{
	int status = 0;
	pid_t pid;
	
	pid = fork();
	
	if(pid != 0)
	{
		if(!arguments->amp)
			waitpid(pid, &status, 0);
	}
	else if(pid == 0)//child
	{
		if(arguments->pipe)
		{
			pipeIt(arguments, histList, aliasList);
		}
		else
		{
			execvp(arguments->prePipe[0], arguments->prePipe);
			
			cleanargs(arguments);
			clearHistList(histList);
			clearAliasList(aliasList);
			fprintf(stderr, "Unknown command.\n");
			exit(0);
		}
	}
}

void pipeIt(Arg *arguments, LinkedList *histList, LinkedList *aliasList)
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
		
		if(execvp(arguments->prePipe[0], arguments->prePipe) == -1)
		{
			cleanargs(arguments);
			clearHistList(histList);
			clearAliasList(aliasList);
			fprintf(stderr, "Unknown command.\n");
			exit(-1);
		}
	}
	else
	{
		close(fd[1]);
		close(0);
		dup(fd[0]);
		
		if(execvp(arguments->postPipe[0], arguments->postPipe) == -1)
		{
			cleanargs(arguments);
			clearHistList(histList);
			clearAliasList(aliasList);
			fprintf(stderr, "Unknown command.\n");
			exit(-1);
		}
	}
}// end pipeIt
