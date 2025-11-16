#include "heap.h"


// Funções Auxiliares 


int is_null(Heap *heap) {

    return (heap == NULL);  
}

int is_empty(Heap *heap) {

    return (is_null(heap) || heap->size == 0);
} 

int is_full(Heap *heap) {

    return (is_null(heap) || heap->size == heap->capacity);
}

void free_heap(Heap *heap) {
    if (is_null(heap)) return;

    if (heap->nodes != NULL) {
        free(heap->nodes);
    }
    
    if (heap->vert_index != NULL) { 
        free(heap->vert_index);
    }

    free(heap);
}

int return_parent(int i) {

    return (i - 1) / 2;
}

int return_left_child(int i) {

    return (2 * i) + 1;
}

int return_right_child(int i) {

    return (2 * i) + 2;  
}

Status swap_positions(Heap *heap, int i, int j) {
    if (is_null(heap) || is_empty(heap)) return error;
    if(i >= heap->size || j >= heap->size) return error;
    
    if(i == j) return success;

    if (heap->data != NULL) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[j];
        heap->data[j] = temp;
    } else {
        HeapNode temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[j];
        heap->nodes[j] = temp;

        heap->vert_index[heap->nodes[i].vert] = i;
        heap->vert_index[heap->nodes[j].vert] = j;
    }

    return success;
}

int compare_priority(Heap *heap, int i, int j) {
    if (heap->data != NULL) {
        return heap->data[i] > heap->data[j];  
    } else {
        return heap->nodes[i].priority < heap->nodes[j].priority;  
    }
}

Status heapify_down(Heap *heap, int i) {
    if(is_null(heap) || is_empty(heap)) return error;
    if( i >= heap->size) return error;

    int l = return_left_child(i);
    int r = return_right_child(i);
    int key = i;

    if(l < heap->size && compare_priority(heap, l, key)) {
        key = l;
    } 

    if(r < heap->size && compare_priority(heap, r, key)) {
        key = r;
    }

    if(key != i) {
        swap_positions(heap, i, key);
        heapify_down(heap, key);
    }

    return success;
}

Status heapify_up(Heap *heap, int i) {
    if(is_null(heap) || is_empty(heap)) return error;
    if(i >= heap->size) return error;

    int p = return_parent(i);

    if(p >= 0 && compare_priority(heap, i, p)) {
        swap_positions(heap, p, i);
        heapify_up(heap, p);
    }

    return success;
}


// Funções para HeapSort

Heap* create_simple_heap(int *array, int size) {
    Heap *heap = malloc(sizeof(Heap));
    if (is_null(heap)) return NULL;

    heap->capacity = size;
    heap->data = array;
    heap->size = size;
    heap->nodes = NULL;
    heap->vert_index = NULL;

    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }

    return heap;
}

void heap_sort(int *array, int n) {
    if (is_null(array) || n <= 0) return;
    Heap *heap = create_simple_heap(array, n);
    
    for (int i = n - 1; i > 0; i--) {
        swap_positions(heap, 0, i);
        heap->size--;
        heapify_down(heap, 0);
    }

    free(heap);
}


// Funções para o Algoritmo de Dijkstra 


Heap* create_dijkstra_heap(int vert_num) {
    Heap *heap = malloc(sizeof(Heap));
    if (is_null(heap)) return NULL;

    heap->capacity = vert_num;
    heap->size = vert_num;
    heap->data = NULL;
        
    heap->nodes = malloc(vert_num * sizeof(HeapNode));
    heap->vert_index = malloc(vert_num * sizeof(int));
    if (heap->nodes == NULL || heap->vert_index == NULL) {
        if (heap->nodes != NULL) free(heap->nodes);
        if (heap->vert_index != NULL) free(heap->vert_index);
        free(heap);

        return NULL;
    }

    for (int i = 0; i < vert_num; i++) {
        heap->nodes[i].vert = i;
        heap->nodes[i].priority = INF;  
        heap->vert_index[i] = i;
    }

    for(int i = vert_num / 2 - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }

    return heap;
}

Status end_insert(Heap *heap, int vert, int priority) {
    if(is_null(heap) || is_full(heap)) return error;

    heap->nodes[heap->size].vert = vert;
    heap->nodes[heap->size].priority = priority;
    heap->vert_index[vert] = heap->size;

    heap->size++;
    heapify_up(heap, heap->size - 1);

    return success;
}

HeapNode remove_min(Heap *heap) {
    if(is_null(heap) || is_empty(heap)) return (HeapNode){-1, -1};

    HeapNode min_value = heap->nodes[0];
    heap->vert_index[min_value.vert] = -1;
    heap->size--;

    if(heap->size > 0) {
        heap->nodes[0] = heap->nodes[heap->size];
        heap->vert_index[heap->nodes[0].vert] = 0;  

        heapify_down(heap, 0);
    }

    return min_value;
}

Status decrease_priority(Heap *heap, int vert, int new_priority) {
    if(is_null(heap) || is_empty(heap)) return error;
    if (vert < 0 || vert >= heap->capacity) return error;
    
    int vert_index = heap->vert_index[vert];
    if(vert_index == -1 || vert_index >= heap->size) return error;

    if(new_priority >= heap->nodes[vert_index].priority) return error;
    
    heap->nodes[vert_index].priority = new_priority;
    heapify_up(heap, vert_index);
    return success;
}




