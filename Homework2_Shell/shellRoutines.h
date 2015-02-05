//Chris Park

#ifndef SHELLROUTINES_H
#define SHELLROUTINES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "linkedList.h"
#include "parsing.h"
#include "cleaning.h"

void forkIt(Arg *arguments, LinkedList *histList, LinkedList *aliasList);
void clean(int argc, char **args);
void pipeIt(Arg *arguments, LinkedList *histList, LinkedList *aliasList);

#endif //SHELLROUTINES_H
