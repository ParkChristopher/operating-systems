//Chris Park

#include "cleaning.h"

void clean(int argc, char **args)
{
	int i;
	
	for(i = 0; i < argc + 1; i++)
		free(args[i]);
	 
	free(args);
}

void cleanargs(Arg *arguments)
{
	clean(arguments->prenum, arguments->prePipe);
	
	if(arguments->postPipe != NULL)
		clean(arguments->postnum, arguments->postPipe);
	
	free(arguments);
}

void removeAlias(char *s, LinkedList *aliasList)
{
	Node *temp, *previous;
	Aliases *check;
	
	check = aliasList->head->data;
	//Head Case
	if(strcmp(check->key, s) == 0)
	{
		temp = aliasList->head;
		aliasList->head = aliasList->head->next;
		
		free(check->key);
		free(check->val);
		free(check);
		free(temp);
		
		aliasList->size--;
		
		return;
	}
	
	//Standard Case
	previous = aliasList->head;
	for(temp = aliasList->head; temp != NULL; temp = temp->next)
	{
		check = temp->data;
		if(strcmp(check->key, s) == 0)
		{
			previous->next = temp->next;
			
			free(check->key);
			free(check->val);
			free(check);
			free(temp);
			
			aliasList->size--;
			
			return;
		}
		
		previous = temp;
	}
}
