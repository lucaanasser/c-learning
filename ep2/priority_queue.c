#include "priority_queue.h"

// Função para liberar a memória
void free_pq(Priority_Queue *pq) {
    if(pq_is_null(pq)) return;

    if(pq->type == heap) {
        free_heap(pq->heap);
    } else {
        free_list(pq->list);
    }

    free(pq);
}

int pq_is_null(Priority_Queue *pq) {

    return (pq == NULL);
}

int pq_is_empty(Priority_Queue *pq) {
    if(pq_is_null(pq)) return 1;

    if(pq->type == heap) {
        return heap_is_empty(pq->heap);
    } else {
        return list_is_empty(pq->list);
    }
}

int pq_is_full(Priority_Queue *pq) {
    if(pq_is_null(pq)) return 1;

    if(pq->type == heap) {
        return heap_is_full(pq->heap);
    } else {
        return 0;
    }
}

// Funções auxiliares
Priority_Queue *create_pq(Priority_Queue_Type type, int vert_num) {
    if(type == heap) {
        Priority_Queue *pq = (Priority_Queue *)malloc(sizeof(Priority_Queue));
        if(pq_is_null(pq)) return NULL;

        pq->type = heap;
        pq->heap = create_min_heap(vert_num);

        return pq;
    } else {
        Priority_Queue *pq = (Priority_Queue *)malloc(sizeof(Priority_Queue));
        if(pq_is_null(pq)) return NULL;
        
        pq->type = linked_list;
        pq->list = create_list();

        return pq;
    }
}

Status pq_insert_sorted(Priority_Queue *pq, Edge data) {
	if(pq_is_null(pq)) return error;

	if(pq->type == heap) {
        if(pq_is_full(pq)) return error;
        return heap_insert_sorted(pq->heap, data);
    } else {
        return list_insert_sorted(pq->list, data);
    }
}

Edge pq_remove_min(Priority_Queue *pq) {
	if(pq_is_empty(pq)) return (Edge){-1,-1};

	if(pq->type == heap) {
		Edge min = heap_remove_min(pq->heap);

		return min;
    } else {
        Edge min = list_remove_min(pq->list);

        return min;
    }
}

Edge pq_return_min(Priority_Queue *pq) {
	if(pq_is_empty(pq)) return (Edge){-1,-1};

	if(pq->type == heap) {
		Edge min = heap_return_min(pq->heap);

		return min;
    } else {
        Edge min = list_return_min(pq->list);

        return min;
    }
}

Status pq_decrease_priority(Priority_Queue *pq, int vert, int new_priority) {
	if(pq_is_empty(pq)) return error;

	if(pq->type == heap) {
		return heap_decrease_priority(pq->heap, vert, new_priority);
    } else {
		return list_decrease_priority(pq->list, vert, new_priority);
    }
}