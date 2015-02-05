//Chris Park

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    void * data;
    struct node * next;
};
typedef struct node Node;

struct linkedlist
{
    Node * head;
    int size;
    int HISTFILECOUNT;
    int HISTCOUNT;
};
typedef struct linkedlist LinkedList;

struct com
{
	int num;
	char *theCommand;
};
typedef struct com commands;

struct argmnts
{
	int pipe;
	int amp;
	int prenum;
	int postnum;
	char redirect;
	char **prePipe;
	char **postPipe;
	char *filename;
};
typedef struct argmnts Arg;

struct alias
{
	char * key;
	char * val;
};
typedef struct alias Aliases;

LinkedList * linkedList();

Node * buildHistNode(char *s, int num);
commands * buildCommand(char *s, int num);
void sort(LinkedList *theList);
void clearHistList(LinkedList *theList);
void clearAliasList(LinkedList *theList);
Node * buildAliasNode(char *key, char *val);
Aliases * buildAlias(char *key, char *val);
void shiftHistory(char *s, LinkedList *histList);
void resizeHistory(LinkedList * histList);

void printList(LinkedList * theList);
void addLast(LinkedList * theList, Node * nn);
void addFirst(LinkedList * theList, Node * nn);
void removeItem(LinkedList * theList, Node * nn);


#endif // LINKEDLIST_H
