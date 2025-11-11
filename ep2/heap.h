#ifndef _HEAP_
#define _HEAP_

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    min,
    max
} HeapType;  


typedef struct Heap {
    int *data;      
    int size;     
    int capacity;
    HeapType type; 
} Heap;



#endif
