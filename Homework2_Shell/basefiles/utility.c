//Chris Park CSCD340

#include "utility.h"

int menu()
{
    int choice;

    printf("\n1)Print the List\n"
    "2)Add First\n"
    "3)Add Last\n"
    "4)Sort the List (ascending order)\n"
    "5)Delete a Word\n"
    "6)Quit --\n\n");

    while (1)
    {
        printf("Enter Choice: ");
        scanf("%d", &choice);
        if (choice > 0 && choice < 7)
            break;

        printf("Invalid Choice.\n");
    }

    return choice;
}

FILE * openFile()
{
    FILE * p_infile;
    char filename[MAX];

    while(1)
    {
        printf("Enter Filename: ");
        scanf("%s", filename);
        p_infile = fopen(filename, "r");

        if (p_infile != NULL)
            break;

        printf("File not found.\n");
    }

    return p_infile;
}

void strip(char *array)
{
    int i, len;
    len = strlen(array);

    for (i = 0; i < len; i ++)
    {
        if (array[i] == '\n' || array[i] == '\r')
            array[i] = '\0';
        
         if (array[i - 1] == '\n' || array[i - 1] == '\r')
            array[i] = '\0';
    }
}

int countRecords(FILE * fin, int lines)
{
    int count = 0;
    int ch = 0;

    while(!feof(fin))
    {
        ch = fgetc(fin);
        if (ch == '\n')
        count++;
    }

    if (count == 0)
    {
        perror("Record Count is 0.");
        exit(1);
    }

    return count/lines;
}

void buildList(LinkedList * myList, FILE * fin, int total)
{
    int i, len;
    char str[MAX];
    Node * nn;

    rewind(fin);
    for(i = 0; i < total; i ++)
    {
        fgets(str, MAX, fin);
        strip(str);
        len = strlen(str);
        nn = malloc(sizeof(Node));
        nn->data = malloc((len + 1) * sizeof(char));
        strcpy(nn->data, str);
        addLast(myList, nn);
    }

    fclose(fin);
}
