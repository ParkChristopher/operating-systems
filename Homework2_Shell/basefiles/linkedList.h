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

struct com
{
	int num;
	char *theCommand;
};
typedef struct com commands;

struct linkedlist
{
    Node * head;
    int size;
};
typedef struct linkedlist LinkedList;


LinkedList * linkedList();

Node * buildNode(char *s, int num);
commands * buildCommand(char *s, int num);
void sort(LinkedList * theList);
void clearList(LinkedList * theList);

void printList(LinkedList * theList);
void addLast(LinkedList * theList, Node * nn);
void addFirst(LinkedList * theList, Node * nn);
void removeItem(LinkedList * theList, Node * nn);


#endif // LINKEDLIST_H
