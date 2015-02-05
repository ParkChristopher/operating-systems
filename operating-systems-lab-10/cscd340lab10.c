//Chris Park

#include "convert.h"
#include "paging.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int getFrame(int frames[], int size, int * eviction);

int vasSize = 1048576;
int pasSize = 65536;
int pageSize = 256;

int main()
{
	FILE * fp;
	char filename[MAX];
	int address, i, j, miss, hit, evict, pageNum;
	int translated, numEvict;
	PTE vas[vasSize / pageSize];
	int pframes[pasSize / pageSize]; 
	int offset = getBits(pageSize);
	char curPage[MAX_BITS - offset];
	char binAddress[MAX_BITS];
	char phys[offset];
	translated = numEvict = miss = hit = evict = 0;
	
	for(i = 0; i < (vasSize/pageSize); i ++)
	{
		vas[i].referenced = 0;
		vas[i].refCount = 0;
		vas[i].pframe = -1;
		vas[i].modified = 0;
	}
	
	for(i = 0; i < (pasSize/pageSize); i++)
		pframes[i] = 0;
	
	printf("Enter input filename: ");
	scanf("%s", filename);
	fp = fopen(filename, "r");
	
	while(fscanf(fp, "%d", &address) != EOF)
	{
		translated++;
		
		toBinary(address, binAddress);
		for(i = 0; i < MAX_BITS - offset; i++)
			curPage[i] = binAddress[i];
		
		
		for(i = MAX_BITS - 1, j = offset - 1; i > MAX_BITS - offset; i--)
		{
			phys[j] = binAddress[i];
			j--;
		}
		
		for(i = 0; i < offset; i ++)
			printf("%d", phys[i]);
		
		pageNum = toDecimal(curPage, MAX_BITS - offset);
	
		if(vas[pageNum].referenced == 1)
		{
			hit++;
			vas[pageNum].refCount += 1;
			
			printf("Virtual Address: %d\n", address);
			printf("Page Number: %d\n", pageNum);
			printf("Hit\n");
			printf("Page Frame Number: %d\n", vas[pageNum].pframe);
			printf("Physical Address: %d\n", (vas[pageNum].pframe * pageSize) + toDecimal(phys, offset));
			printf("=========================\n");
		}
		else
		{
			miss++;
			vas[pageNum].pframe = getFrame(pframes, (pasSize/pageSize), &evict);
			vas[pageNum].referenced = 1;
			vas[pageNum].refCount += 1;
			
			printf("Virtual Address: %d\n", address);
			printf("Page Number: %d\n", pageNum);
			printf("Miss\n");
			printf("Page Frame Number: %d\n", vas[pageNum].pframe);
			printf("Physical Address: %d\n", (vas[pageNum].pframe * pageSize) + toDecimal(phys, offset));
			printf("=========================\n");
		}
	}
	
	printf("Number of Translated Addresses = %d\n", translated);
	printf("Page Faults = %d\n", miss);
	printf("Page Fault Rate = %lf\n", (double)miss/translated);
	printf("Page Evictions = %d\n", numEvict);
	printf("Page Eviction Rate = %lf\n", (double)numEvict/translated);
	
	fclose(fp);
	return 0;
}

int getFrame(int frames[], int size, int * eviction)
{
	int i;
	for(i = 0; i < size; i++)
		if(frames[i] == 0)
		{
			frames[i] = 1;
			return i;
		}
		
	if((*eviction) == size)
		(*eviction = 0);
	
	i = (*eviction);
	(*eviction)++;
	
	return i;
}
