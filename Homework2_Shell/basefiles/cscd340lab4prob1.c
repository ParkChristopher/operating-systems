#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "utility.h"

#define MAX 100

void clean(int argc, char **argv);
void printargs(int argc, char **argv);
int makeargs(char *s, char *** argv);
void forkIt(char ** argv, int argc, LinkedList *theList);
void strip(char *s);


int main()
{
	char **argv = NULL, s[MAX];
	int argc = 0, i;
	LinkedList *theList = linkedList();
	Node *nn = NULL;

	do 
	{
		printf("Please enter a command (exit to exit, print to print) ");
		fgets(s, MAX, stdin);
	}
	while(strcmp(s, "\n") == 0);
	
	i = 1;
 	while(strcmp(s, "exit\n") != 0)
  	{
  		
  		if(strcmp(s, "print\n") == 0)
  		{
  			if(theList->size == 0)
  				printf("Empty List.\n");
  			else
  				printList(theList);
  		}
  		
  			if(strcmp(s, "\n") != 0)
  			{
  				nn = buildNode(s, i);
  				addLast(theList, nn);
  				i++;
  		
  				argc = makeargs(s, &argv);
		
  				forkIt(argv, argc, theList);
		
  				clean(argc, argv);
  				argv = NULL;
  			}
  			
  			printf("Please enter a command (exit to exit, print to print) ");
			fgets(s, MAX, stdin);
	}
	
	clearList(theList);
	return 0;
}

void clean(int argc, char **argv)
{
	int i;
	
	for(i = 0; i < argc + 1; i++)
		free(argv[i]);
	 
	free(argv);
}

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}

int makeargs(char *s, char *** args)
{
	int count, i;
	char * save_ptr;
	char *count_ptr = s;
	char *temp;
	
	if(s == NULL)
	{
		printf("No strings.\n");
		exit(-1);
	}
	
	strip(s);
	count = 1;
	while((count_ptr = strchr(count_ptr, ' ')) != NULL)
	{
		count++;
		count_ptr++;
	}
	
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

void forkIt(char ** argv, int argc, LinkedList *theList)
{
	int status;
	pid_t pid;
	status = 0;
	
	pid = fork();
	
	if (pid != 0)
	{
   	    waitpid(-1, &status, 0);
	}
	else
	{
	   execvp(argv[0], argv);
	   
	   clean(argc, argv);
	   clearList(theList);
	   printf("Unknown command.\n");
	   exit(0);
	   
	}
}
