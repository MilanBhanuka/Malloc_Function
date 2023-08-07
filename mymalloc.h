#include<stdio.h>
#include<stddef.h>

char memory[25000];

struct block
{
    size_t size;	//allocated size in memory
    int free;	//Indicate whether memory block free or not
    struct block*next;	 //Include the next memory block address pointer
};

void blockInitialization();
void split(struct block*allocateSlot, size_t size);
void *Mymalloc(size_t availableBytes);
void merge();
void MyFree(void *ptr);