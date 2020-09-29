#include "mm.h"
int main()
{
	void *ptr1,*ptr2,*ptr3;
	//my malloc
	ptr1=mymalloc(16);
	ptr2=mymalloc(32);
	ptr3=mymalloc(16);
	printf("=============================================\n");
	printf("1 unit = 16 bytes\nthe amount of units include header\n\n");
	
	printf("===============my malloc test===============\n\n");
	printf("ptr1 (account 2 units)= %p\n",ptr1);
	printf("ptr2 (account 3 units)= %p\n",ptr2);
	printf("ptr3 (account 2 units)= %p\n",ptr3);
	printf("-----------to test split block-----------\n");
    printf("free ptr2 and then allocate 2 units to it\n");
    myfree(ptr2);
    ptr2=mymalloc(16);
    printf("ptr2 (account 2 units)= %p\n",ptr2);
    printf("-----------to test merge block-----------\n");
    printf("free ptr1 and then allocate 3 unit to it\n");
    myfree(ptr1);
    ptr1=mymalloc(32);
  	printf("ptr1 (account 3 units)= %p\n",ptr1);
  	
  	printf("\n===============my calloc test===============\n\n");
  	int *ptr4;
  	ptr4=(int *)mycalloc(1,sizeof(int));
  	printf("ptr4 (account 2 units)= %p\n",ptr4);
  	printf("*ptr4 value = %d\n",*ptr4);
  	
  	printf("\n===============my realloc test===============\n\n");
  	long int *ptr5;
  	*ptr4=100;
  	ptr5=(long int *)myrealloc(ptr4,sizeof(long int));
  	printf("ptr5 (account 2 units)= %p\n",ptr5);
  	printf("*ptr5 value = %ld\n",*ptr5);
  	printf("\n=============================================\n");
  	return 0;
}
