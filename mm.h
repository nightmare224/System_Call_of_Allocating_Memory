#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void * mymalloc(size_t nbytes);
void * morecore(size_t unith);
void * mycalloc(size_t n,size_t nbytes);
void * myrealloc(void *ptr,size_t nbytes);
void myfree(void *ptr);
