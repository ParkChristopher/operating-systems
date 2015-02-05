//Chris Park

#include "commands.h"

int checkCommands(char* s, Node *aliasNode, LinkedList *aliasList,
	LinkedList *histList)
{
	int histcount, histfilecount, command_num, res;
	char *temp, *temp2, *token, *remove, *quotes;
	char *key, *val, *currentPath, *newPath;
	char *save_ptr, *quote_ptr, *end_ptr;
	
	temp = calloc(strlen(s) + 1, sizeof(char));
	strcpy(temp, s);
	
	token = strtok_r(temp, " =", &save_ptr);
	
	if(token != NULL)
	{
		if(strcmp(token, "history") == 0)
		{
			if(histList->size == 0)
  					printf("Empty History.\n");
  				else
  					printList(histList);
  			
  			free(temp);
  			return 1;
		}//end history
		
		if(strcmp(token, "alias") == 0)
		{	
			key = strtok_r(NULL, "=", &save_ptr);
			val = strtok_r(NULL, "\0", &save_ptr);
			
			if(val == NULL)
			{
				free(temp);
				return 0;
			}
			
			quotes = calloc(strlen(val) + 1, sizeof(char));
			strcpy(quotes, val);
		
			if(quotes[0] == '\"' || quotes[0] == '\'')
			{
				temp2 = strtok_r(quotes, "\"\'", &quote_ptr);
				strcpy(val, temp2);
				free(quotes);
			}
				
			aliasNode = buildAliasNode(key, val);
			addLast(aliasList, aliasNode);
			aliasList->size++;
			
			free(temp);
			return 1;
		}//end alias
		
		if(strcmp(token, "unalias") == 0)
		{
			remove = strtok_r(NULL, "\0", &save_ptr);
			removeAlias(remove, aliasList);
			
			free(temp);
			return 1;
		}// end unalias
		
		if(strcmp(token, "PATH") == 0)
		{
			token = strtok_r(NULL, ":", &save_ptr);
			temp2 = strtok_r(NULL, "\0", &save_ptr);
			
			if(strcmp(token, "$PATH") == 0)
			{
				
				currentPath = getenv("PATH");
				newPath = calloc(strlen(currentPath) + strlen(temp2) + 1,
					sizeof(char));
				
				strcpy(newPath, currentPath);
				strcat(newPath, temp2);
				
				setenv("PATH", newPath, 1);
				
				free(newPath);
				free(temp);
				return 1;
			}	
			
		}//end PATH
		
		if(strcmp(token, "HISTFILECOUNT") == 0)
		{
			token = strtok_r(NULL, "\0", &save_ptr);
			histfilecount = strtol(token, &end_ptr, 10);
			histList->HISTFILECOUNT = histfilecount;
			
			free(temp);
			return 1;
		}//end HISTFILECOUNT
		
		if(strcmp(token, "HISTCOUNT") == 0)
		{
			token = strtok_r(NULL, "\0", &save_ptr);
			histcount = strtol(token, &end_ptr, 10);
			histList->HISTCOUNT = histcount;
			
			free(temp);
			return 1;
		}//end HISTCOUNT
		
		//start !Recall
		if(token[0] == '!')
		{
			if(token[1] == '!')
			{
				temp2 = recallCommand(histList, histList->size);
					
				if(temp2 == NULL)
				{
					fprintf(stderr, "Recall failed\n");
					
					free(temp);
					return 0;
				}
				
				strcpy(s, temp2);
			}
			else
			{
				sscanf(token, "!%d", &command_num);
				temp2 = recallCommand(histList, command_num);
				
				if(temp2 == NULL)
				{
					fprintf(stderr, "Recall failed\n");
					
					free(temp);
					return 0;
				}
				
				strcpy(s, temp2);
			}
		}//end !Recall
		
		
		if(strcmp(token, "cd") == 0)
		{
			token = strtok_r(NULL, "\0", &save_ptr);
			
			if(token != NULL)
				res = chdir(token);
			
			if(res == -1)
				fprintf(stderr, "Invalid path.\n");
			
			free(temp);
			return 1;
		}//end cd
		
		if(strcmp(token, "grep") == 0)
		{
			char* gr;
			char *args;
			
			temp2 = strtok_r(NULL, "\0", &save_ptr);
			
			args = calloc(strlen(temp2) + 2, sizeof(char));
			args[0] = ' ';
			strcat(args, temp2);
			
			gr = calloc(strlen(token) + strlen(args) + 1, sizeof(char));
			strcpy(gr, token);
			strcat(gr, args);
			
			system(gr);
			
			free(args);
			free(gr);
			free(temp);
			return 1;
		}
	}
	
	free(temp);
	return 0;
}

char * recallCommand(LinkedList *histList, int num)
{
	Node *temp;
	commands *check;
	
	for(temp = histList->head; temp != NULL; temp = temp->next)
	{
		check = temp->data;
		
		if(check->num == num)
			return check->theCommand;
	}
	
	return NULL;
}

void historyToFile(LinkedList * histList)
{
	FILE * fp;
	commands * comm;
	Node * temp;
	
	fp = fopen(".mysh_history", "w");
	
	if(histList->HISTFILECOUNT < histList->HISTCOUNT)
	{
		histList->HISTCOUNT = histList->HISTFILECOUNT;
		resizeHistory(histList);
	}
	
	for(temp = histList->head; temp != NULL; temp = temp->next)
	{
		comm = temp->data;
		fprintf(fp, "%s\n", comm->theCommand);
	}
	
	fclose(fp);
	
}

void searchAliases(char * s, LinkedList * aliasList)
{
	Node *temp;
	Aliases *check;
	char *match;
	
	for(temp = aliasList->head; temp != NULL; temp = temp->next)
	{
		check = temp->data;
		if(strcmp(check->key, s) == 0)
		{
			match = calloc(strlen(check->val) + 1, sizeof(char));
			strcpy(match, check->val);
			strcpy(s, match);
			free(match);
			break;
		}
	}
}
