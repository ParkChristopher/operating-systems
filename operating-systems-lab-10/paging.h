//Chris Park

#ifndef PAGING_H
#define PAGING_H



struct pte
{
	int pframe; //decimal
	int referenced; //referenced anytime the page is referenced
	int refCount; //how many times referenced
	int modified; //for future use
};
typedef struct pte PTE;

#endif //PAGING_H
