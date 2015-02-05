//Chris Park

#include "utility.h"

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
    int len;
    len = strlen(array);

    if(array[len - 2] == '\r')
    	array[len - 2] = '\0';
    else if(array[len - 1] == '\n')
    	array[len - 1] = '\0';
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
