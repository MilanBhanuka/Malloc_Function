#include<stdio.h>
#include "mymalloc.h"
#include<stddef.h>

//list pointing to the starting address of the memory that created 
struct block *list=(void*)memory;

//Initialize the first block of memory 
void blockInitialization()
{
    list->size=25000-sizeof(struct block);
    list->free=1;
    list->next=NULL;
    printf("Pointer start_list address is = %d\n", &list);
}


//This function splits the memory block to the two parts which included allocated part and free part
void split(struct block *allocateSlot, size_t size){
    struct block *new = (void*)((void*)allocateSlot+size+sizeof(struct block));
    new->size=(allocateSlot->size)-size-sizeof(struct block);
    new->free=1;
    new->next=allocateSlot->next;

	//current metablock 
    allocateSlot->size=size;
    allocateSlot->free=0;
    allocateSlot->next=new;
} 



//Function to allocate memory
void *Mymalloc(size_t availableBytes)
{
    struct block *currentblock;
    void *result;  //return the starting address of the allocated memory block

	//if memory not initilized this part works
    if(!(list->size))
	{
        blockInitialization();
        
        printf("Memory initialized\n");
    }
    
    //store current block address
    currentblock=list;
	
	//traverse the memory until find the block to allocate 
    while ((((currentblock->size)<availableBytes)||((currentblock->free)==0))&&(currentblock->next!=NULL))
	{
        currentblock=currentblock->next;
        printf("One block checked\n");
    }

	//If the size of bytes which want to allocated equal to the freed memory block this conditon works    
    if((currentblock->size)==availableBytes)
	{
        currentblock->free=0;
        result=(void*)(++currentblock);
        printf("Exact fitting block allocated\n");
        return result;
    }
    
    //If the size of bytes which want to allocated is less than to the freed memory block then split the memory block and allocate
    else if((currentblock->size)>(availableBytes+sizeof(struct block)))
	{
        split(currentblock,availableBytes);
        
        result=(void*)(++currentblock);
        printf("Fitting block allocated with a split\n");
        return result;
    }
    
    //If the size of bytes which want to allocated is more than to any freed memory block
    else
	{
    	
        result=NULL;
        printf("Sorry. No sufficient memory space to allocate\n");
        return result;
    }    
}

//if there are 2 or more free slots together,then they connect those slot to one slot
void merge(){
    struct block *currentblock;
    currentblock=list;

    while((currentblock->next)!=NULL){
        if((currentblock->free)&&(currentblock->next->free)){
            currentblock->size+=(currentblock->next->size)+sizeof(struct block);
            currentblock->next=currentblock->next->next;
        }
        currentblock=currentblock->next;
    }
}


//Deallocate the memory 
void MyFree(void* ptr){
	//check wheather ptr is include in memory
    if(((void*)memory<=ptr)&&(ptr<=(void*)(memory+25000)))
	{
        struct block *temp=ptr;
        --temp;
        temp->free=1;
        merge();
        printf("block Freed successfully\n\n"); 
    }
	else
	{
        printf("Please provide a valid pointer allocated by Mymalloc\n\n");
    }
}
