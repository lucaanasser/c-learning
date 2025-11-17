#ifndef _HEAP_
#define _HEAP_

#include "list.h"
#define INF 42424242 

typedef enum {
    max_heap,
    min_heap
} Heap_Type;

typedef struct Heap {
    Heap_Type type;
    int size;            
    int capacity;        
    
    union {
        int *data;           
        Edge *nodes;     
    };
    
    int *vert_index;      
} Heap;

void free_heap(Heap *heap);

int heap_is_null(Heap *heap);
int heap_is_empty(Heap *heap);
int heap_is_full(Heap *heap);


// Heap sort 
Heap* create_max_heap(int *array, int size);

void heap_sort(int *array, int size);

// Dijkstra Heap
Heap* create_min_heap(int vert_num);

Status heap_insert_sorted(Heap *heap, Edge data);
Edge heap_remove_min(Heap *heap);
Edge heap_return_min(Heap *heap);
Status heap_decrease_priority(Heap *heap, int vertex, int new_priority);

#endif
