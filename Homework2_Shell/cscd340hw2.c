//Chris Park

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "shellRoutines.h"
#include "commands.h"
#include "utility.h"
#include "cleaning.h"

#define MAX 100

void loadSettings(Node * aliasNode, LinkedList * aliasList,LinkedList * histList);
int loadHistory(Node *aliasNode, LinkedList * aliasList,
	LinkedList * histList, Node * histNode);

int main()
{
	int isFork, isPipe, isCommand, i;
	char s[MAX];
	char redir;
	LinkedList *histList = linkedList();
	LinkedList *aliasList = linkedList();
	Node *histNode = NULL;
	Node *aliasNode = NULL;
	Arg *arguments = NULL;
	
	loadSettings(aliasNode, aliasList, histList);
	i = loadHistory(aliasNode, aliasList, histList, histNode);
	
	printf("?: ");
	fgets(s, MAX, stdin);

 	while(strcmp(s, "exit\n") != 0)
  	{
  		if(strcmp(s, "\n") != 0)
  		{
  			strip(s);
  			
  			isCommand = checkCommands(s, aliasNode, aliasList, histList);
  			
  			histNode = buildHistNode(s, i);
  			addLast(histList, histNode);
  			i++;
  			
  			if(!isCommand)
  			{
  				searchAliases(s, aliasList);
  				
				isFork = checkOperator(s);
				redir = checkRedir(s);
				isPipe = checkPipe(s);
				
				arguments = constructArgs(isFork, isPipe, redir, s);
				forkIt(arguments, histList, aliasList);
				
				cleanargs(arguments);
				arguments = NULL;
			}
		}
		printf("?: ");
		fgets(s, MAX, stdin);

	}// end while
	historyToFile(histList);
	clearHistList(histList);
	clearAliasList(aliasList);
	
	return 0;
}// end main

void loadSettings(Node * aliasNode, LinkedList * aliasList,LinkedList * histList)
{
	char  str[MAX];
	FILE * in;
	
	in = fopen(".myshrc", "r");
	
	if(in == NULL)
	{
		fprintf(stderr, ".myshrc file not found\n");
		return;
	}
	
	fgets(str, MAX, in);
	while(!feof(in))
	{
		strip(str);
		checkCommands(str, aliasNode, aliasList, histList);
		fgets(str, MAX, in);
	}
		
	fclose(in);
}

int loadHistory(Node *aliasNode, LinkedList * aliasList,
	LinkedList * histList, Node * histNode)
{
	int histSize;
	char str[MAX];
	FILE * in;
	
	in = fopen(".mysh_history", "r");
	
	if(in == NULL)
	{
		fprintf(stderr, ".mysh_history file not found\n");
		return 1;
	}
	
	histSize = 1;
	fgets(str, MAX, in);
	while(!feof(in))
	{
		strip(str);
		histNode = buildHistNode(str, histSize);
		addLast(histList, histNode);
		histSize++;
		fgets(str, MAX, in);
	}
	
	fclose(in);
	return histSize;
}

