#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include "heap.h"
#include "list.h"

typedef enum {
    array,
    linked_list
}Priority_Queue_Type;

typedef struct Priority_Queue {
    Priority_Queue_Type type;
    union {
        Heap *array_priority_queue;
        LinkedList *list_priority_queue;
    }
}

#endif
