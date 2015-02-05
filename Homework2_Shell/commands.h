//Chris Park

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "linkedList.h"
#include "cleaning.h"

int checkCommands(char* s, Node *aliasNode, LinkedList *aliasList,
	LinkedList *histList);
void searchAliases(char * s, LinkedList * aliasList);
char * recallCommand(LinkedList *histList, int num);
void historyToFile(LinkedList * histList);

#endif //COMMANDS_H
