#ifndef _HEAP_
#define _HEAP_

#include <stdio.h>
#include <stdlib.h>
#define INF 42424242 

typedef enum {
    success = 0,
    error = -1
} Status;

typedef struct HeapNode {
    int vert;      
    int priority;    
} HeapNode;

typedef struct Heap {
    int size;            
    int capacity;        
    
    union {
        int *data;           
        HeapNode *nodes;     
    };
    
    int *vert_index;      
} Heap;

void free_heap(Heap *heap);
int is_null(Heap *heap);    
int is_empty(Heap *heap);
int is_full(Heap *heap);

Heap* create_simple_heap(int *array, int size);
void heap_sort(int *array, int size);

Heap* create_dijkstra_heap(int vert_num);
Status end_insert(Heap *heap, int vert, int priority);
Status decrease_priority(Heap *heap, int vertex, int new_priority);
HeapNode remove_min(Heap *heap);

#endif
