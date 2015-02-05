//Chris Park CSCD340

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 100

void pipeIt(char ** prePipe, char ** postPipe, int res, int res2);
int makeargs(char *s, char *** args);
void clean(int argc, char **argv);
void strip(char *array);

int main()
{
	int res, res2;
	char s[MAX];
	char ** prePipe = NULL, ** postPipe = NULL;
	char *save_ptr;
	char *temp;
	
	do
	{
		printf("Please enter a string (exit to exit) ");
		fgets(s, MAX, stdin);
	}
	while(strcmp(s, "\n") == 0);
		
	while(strcmp(s, "exit\n") != 0)
	{
		if (strcmp(s, "\n") != 0)
		{
			strip(s);
			temp = strtok_r(s, "|", &save_ptr);
			res = makeargs(temp, &prePipe);
			
	
			temp = strtok_r(NULL, "|", &save_ptr);
			
			if(temp != NULL)	
			{
				res2 = makeargs(temp, &postPipe);
			
				pipeIt(prePipe, postPipe, res, res2);
				clean(res2, postPipe);
			}
			
			clean(res, prePipe);
		}
		
		printf("Please enter a string (exit to exit) ");
		fgets(s, MAX, stdin);

	}// end while
}// end main

void pipeIt(char ** prePipe, char ** postPipe, int res, int res2)
{
	if(fork() == 0)//in the child
	{
		int fd[2];
		
		if(pipe(fd) < 0)
		{
			printf("Failure.");
			exit(0);
		}
		
		if(fork() == 0)//in the grandchild
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			
			if(execvp(prePipe[0], prePipe) == -1)
			{
				clean(res2, postPipe);
				clean(res, prePipe);
				fprintf(stderr, "Unknown command.\n");
				prePipe = NULL;
				exit(-1);
			}
		}
		else
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			
			if(execvp(postPipe[0], postPipe) == -1)
			{
				clean(res, prePipe);
				clean(res2, postPipe);
				fprintf(stderr, "Unknown command.\n");
				prePipe = NULL;
				exit(-1);
			}
		}
	}
	else
	{
		int status;
		
		waitpid(-1, &status, 0);
	}
}// end pipeIt

int makeargs(char *s, char *** args)
{
	int count, i;
	char * save_ptr;
	char *count_ptr = s;
	char *temp;
	int len = strlen(s);
	
	if(s == NULL || strcmp(s, "\n") == 0)
	{
		printf("Invalid Input\n");
		exit(-1);
	}
	
	count = 0;
	
	if(s[0] != ' ')
		count++;
	
	while((count_ptr = strchr(count_ptr, ' ')) != NULL)
	{
		count++;
		count_ptr++;
	}
	
	if(s[len - 1] == ' ')
		count--;
	
	(*args) = (char**)calloc(count + 1, sizeof(char*));
	
	temp = strtok_r(s, " ", &save_ptr);
	(*args)[0] = (char*)calloc(strlen(temp) + 1, sizeof(char));
	strcpy((*args)[0], temp);
	
	for(i = 1; i < count; i++)
	{
		temp = strtok_r(NULL, " ", &save_ptr);
		(*args)[i] = (char*)calloc(strlen(temp) + 1, sizeof(char));
		strcpy((*args)[i], temp);
	}
	(*args)[count] = NULL;
	
	return count;
}

void clean(int argc, char **argv)
{
	int i;
	
	for(i = 0; i < argc + 1; i++)
		free(argv[i]);
	 
	free(argv);
}

void strip(char *array)
{
    int i, len;
    len = strlen(array);

    if(array[len - 2] == '\r')
    	array[len - 2] = '\0';
    else if(array[len - 1] == '\n')
    	array[len - 1] = '\0';
}