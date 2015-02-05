//Chris Park CSCD430

#include "linkedList.h"
#include "utility.h"

LinkedList * linkedList()
{
    LinkedList * theList;
    theList = malloc(sizeof(LinkedList));
    theList->head = NULL;
    theList->size = 0;

    return theList;
}

Node * buildNode(char *s, int num)
{
    Node * nn = malloc(sizeof(Node));
 
    nn->data = buildCommand(s, num);
    
    return nn;
}

commands * buildCommand(char *s, int num)
{
	int len;
	char *str = s;
	commands * comm;
	
	strip(str);
	comm = malloc(sizeof(commands));
	len = strlen(str);
	comm->theCommand = malloc((len + 1) * sizeof(char));
	strcpy(comm->theCommand, str);
	comm->num = num;
	
	return comm;
}

void sort(LinkedList * theList)
{
    int i;
    Node * temp;
    void * swap;

    for (i = 0; i < theList->size; i ++)
        for(temp = theList->head; temp->next != NULL;
            temp = temp->next)
                if (strcmp(temp->data, temp->next->data) > 0)
                {
                    swap = temp->data;
                    temp->data = temp->next->data;
                    temp->next->data = swap;
                }
}

void clearList(LinkedList * theList)
{
    Node * temp;
    commands *tempcomm;

    while (theList->head != NULL)
    {
    	//free command data
    	
        temp = theList->head;
        tempcomm = (commands*)temp->data;
        free(tempcomm->theCommand);
        free(temp->data);
        theList->head = theList->head->next;
        free(temp);
    }
    free(theList);
}

void printList(LinkedList * theList)
{
    Node * temp;
    commands * tempcomm;

    for (temp = theList->head; temp != NULL; temp = temp->next)
    {
    	tempcomm = temp->data;
        printf("%d %s\n", tempcomm->num, (char*)tempcomm->theCommand);
    
    
    
    
    }
}
void addLast(LinkedList * theList, Node * nn)
{
    Node * temp;

    if (theList->head == NULL)
    {
        addFirst(theList, nn);
        return;
    }

    for ( temp = theList->head; temp->next != NULL;
        temp = temp->next);

    temp->next = nn;
    nn->next = NULL;

    theList->size++;
}

void addFirst(LinkedList * theList, Node * nn)
{
    nn->next = theList->head;
    theList->head = nn;

    theList->size++;
}

void removeItem(LinkedList * theList, Node * nn)
{
    Node * temp;
    Node * remove;
    Node * previous;

    //Empty List
    if (theList->size == 0)
    {
        printf("List is Empty.\n");
        return;
    }

    //Head case
    if (strcmp(theList->head->data, nn->data) == 0)
    {
        remove = theList->head;
        theList->head = theList->head->next;

        free(remove->data);
        free(remove);
        free(nn->data);
        free(nn);

        theList->size--;
        printf("Item deleted.\n");

        return;
    }

    //Standard Case
    previous = theList->head;
    for(temp = theList->head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->data, nn->data) == 0)
        {
            remove = temp;
            previous->next = temp->next;

            free(remove->data);
            free(remove);
            free(nn->data);
            free(nn);

            theList->size--;
            printf("Item deleted.\n");

            return;
        }

        previous = temp;
    }

    free(nn->data);
    free(nn);

    printf("Item not found.\n");
}
