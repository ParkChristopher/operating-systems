//Chris Park

#ifndef CLEANING_H
#define CLEANING_H

#include "linkedList.h"


void clean(int argc, char **args);
void cleanargs(Arg *arguments);
void removeAlias(char *s, LinkedList *aliasList);


#endif //CLEANING_H
