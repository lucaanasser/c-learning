#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include "heap.h"
#include "list.h"

typedef enum {
    heap,
    linked_list
} Priority_Queue_Type;

typedef struct Priority_Queue {
    Priority_Queue_Type type;

    union {
        Heap *heap;
        LinkedList *list;
    };
} Priority_Queue;


void free_pq(Priority_Queue *pq);
int pq_is_empty(Priority_Queue *pq);
int pq_is_full(Priority_Queue *pq);
int pq_is_null(Priority_Queue *pq);

Priority_Queue *create_pq(Priority_Queue_Type type, int vert_num);

Status pq_insert_sorted(Priority_Queue *pq, Edge data);
Edge pq_remove_min(Priority_Queue *pq);
Edge pq_return_min(Priority_Queue *pq);
Status pq_decrease_priority(Priority_Queue *pq, int vert, int new_priority);

#endif
