# malloc
---

This project is a recreation of dynamic allocation and memory management library. This functions that are recoded are :-
```C
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *free(void *ptr);
void show_alloc_mem();
```

## Function description
- ``malloc(size_t size)`` function allocates "size" bytes of continuous allocated memory and returns a pointer to the first byte of the allocated memory.
- ``realloc(void *ptr, size_t size)`` function changes the size of "ptr" to "size" bytes. If "ptr" is a ``NULL`` pointer it acts same as ``malloc`` and if the "size" is ``0`` then this function acts ``free``. Also the original data upto "size" bytes if preserved.
- ``free(void *ptr)`` function frees / deallocates the memory allocated from ``malloc`` or ``realloc``
- ``show_alloc_mem(void)`` function prints the stats of the memory allocated to the standard output

## Installation and execution

This project is implemented in C and requires ``make`` and ``gcc`` to run
This project can compiled and executed on Linux as well as MacOS.

To compile and create the library use : ``make`` command in the root directory

Which should create a shared library, ``libft_malloc_$HOSTTYPE.so`` and a link to shared library ``libft_malloc.so``.
**$HOSTTYPE** is machine specific, for example a x86 machine running Linux would give out something like ``libft_malloc_x86_64_Linux.so``

To run a executable and making it use the malloc library we compiled instead the standard library we should use the run scripts For linux it is - **run_linux.sh** and for MacOS it is - **run_mac.sh**. An example in Linux would be
```sh
./run_linux.sh ./a.out
```
where **a.out** is an excutable file
