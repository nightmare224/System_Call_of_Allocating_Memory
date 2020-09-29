#include "mm.h"
typedef struct header Header;
struct header{
    size_t size; //unit of header
    Header *next;
};
Header handle={0,NULL};
Header *freeptr=NULL;
void * mymalloc(size_t nbytes)
{
    size_t unith=(nbytes-1)/sizeof(Header)+2;		//1 units= 1 Header size(16 bytes)
    
    Header *prevptr,*currentptr;
    if(freeptr==NULL){			//initialize
        freeptr=&handle;
        handle.next=&handle;
    }
    prevptr=freeptr;
    
    for(currentptr=freeptr->next;;prevptr=currentptr,currentptr=currentptr->next){	//search in free list
        if(currentptr->size>=unith){			//find first fit
        	if(currentptr->size==unith){		//exactly match
        		prevptr->next=currentptr->next;
           	}else{								//split excess block back to free list
                currentptr->size-=unith;
                currentptr+=currentptr->size;	
                currentptr->size=unith;
            }  
            freeptr=prevptr;
        	return (void *)(currentptr+1);		//header cost one unit
        	
        }else if(currentptr==freeptr){			//can't find fit block 
        	currentptr=morecore(unith);			//so create new block
        	if(currentptr==NULL)				//create failed
        		return NULL;
			currentptr->size=unith;				
        	return (void *)(currentptr+1);		
        }
        	
    }
}
void * morecore(size_t unith)
{
    char *p=sbrk(sizeof(Header)*unith);
    if(*p==-1)				//allocate memory failed
        return NULL;
    return (Header *)p;
}
void * mycalloc(size_t n,size_t nbytes)
{
	Header *ptr=(Header *)mymalloc(n*nbytes);	
	if(ptr==NULL)
		return NULL;
	ptr--;										//get header
	double *ptrd=(double *)(ptr+1);				//set 8 bytes to zero one time
	
	for(;ptrd<=(double *)(ptr+ptr->size);ptrd++)
		*ptrd=0;
	return (void *)(ptr+1);
}
void * myrealloc(void *ptr,size_t nbytes)
{
	//ptr=malloc(nbytes)	

	if(ptr==NULL)		
		return NULL;
	
	double *dptr;
	size_t unith;
	if(nbytes==0){		//if nbytes is 0 free the ptr
		myfree(ptr);
		ptr=NULL;
		
	}else{				//copy data to new position
		dptr=(double *)mymalloc(nbytes);	
		unith=((Header *)(ptr)-1)->size;
		for(size_t i=0;i<(unith-1)<<1;i++)
			*(dptr+i)=*(double *)(ptr+i);
		
		myfree(ptr);	//free original position
		ptr=(void *)dptr;
	}
	
	return ptr;
}
void myfree(void *ptr)
{
	Header *currentptr=(Header *)ptr-1,*hptr;
	for(hptr=&handle;;hptr=hptr->next)					//start search at handle
		if(currentptr<hptr->next||hptr->next==&handle){	
			currentptr->next=hptr->next;				//cuurentptr block should be at the right side of hptr block
			hptr->next=currentptr;
			break;
		}	
		
	//to merge
	if((hptr+hptr->size+currentptr->size)==currentptr->next){		//merge 3 block. [hptr,currentptr,hptr->next]
		hptr->size=hptr->size + currentptr->size + currentptr->next->size;  
		hptr->next=currentptr->next->next;
			
	}else if((hptr+hptr->size)==currentptr ){	//merge with left side block.	[hptr,currentptr]
		hptr->size+=currentptr->size;
		hptr->next=currentptr->next;
	}else if((currentptr+currentptr->size)==currentptr->next){	//merge with right side block[currentptr,hptr->next]
		currentptr->size+=currentptr->next->size;
		currentptr->next=currentptr->next->next;
	}
		

}
