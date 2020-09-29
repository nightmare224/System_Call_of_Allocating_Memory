# System_Call_of_Allocating_Memory
some system call to allocate memory in C language

> This is the homework4 of Operating System course in 2018~2019 Spring Semester.</br>
> This project to implement a memory manager in C, include malloc(), calloc(), realloc(), and free().</br>
> To implement this homework, I reference the book, "The C Programming Language".

### Some Concept

#### concept 1 (
<pre>
<b>The Description from man Page</b>
     The malloc(), calloc(), realloc(), and functions
     allocate memory.  The allocated memory is aligned such that it can be
     used for any data type, including AltiVec- and SSE-related types.  The
     free() function frees allocations that were created via the preceding
     allocation functions.

     The <b>malloc()</b> function allocates size bytes of memory and returns a
     pointer to the allocated memory.

     The <b>calloc()</b> function contiguously allocates enough space for count
     objects that are size bytes of memory each and returns a pointer to the
     allocated memory.  The allocated memory is filled with bytes of value
     zero.
     
     The <b>realloc()</b> function tries to change the size of the allocation pointed
     to by ptr to size, and returns ptr.  If there is not enough room to
     enlarge the memory allocation pointed to by ptr, realloc() creates a new
     allocation, copies as much of the old data pointed to by ptr as will fit
     to the new allocation, frees the old allocation, and returns a pointer to
     the allocated memory.  If ptr is NULL, realloc() is identical to a call
     to malloc() for size bytes.  If size is zero and ptr is not NULL, a new,
     minimum sized object is allocated and the original object is freed.  When
     extending a region allocated with calloc(3), realloc(3) does not guaran-
     tee that the additional memory is also zero-filled.
     
     The <b>free()</b> function deallocates the memory allocation pointed to by ptr.
     If ptr is a NULL pointer, no operation is performed.
</pre>


#### concept 2
<pre>
The mimimum units to request is 1 Header block which is 16 bytes. In other word,</br>
if the request size is less than 16 bytes, the program will assume you need 16 bytes.
</pre>

#### concept 3
<pre>
We can implement realloc() and calloc() by wrappers malloc()
</pre>
