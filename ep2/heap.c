#include "heap.h"

// ========== Funções Auxiliares Gerais ==========

int is_null(Heap *heap) {
    return (heap == NULL);  
}

 int is_empty(Heap *heap) {
    return (heap == NULL || heap->size == 0);
} 

int is_full(Heap *heap) {
    return (heap != NULL && heap->size == heap->capacity);  
}

void free_heap(Heap *heap) {
    if (is_null(heap)) return;

    free(heap->data);
    free(heap->nodes);
    free(heap->vert_index);
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
    if (is_null(heap) || is_empty(heap) || i >= heap->size || j >= heap->size) return error;

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

    return pass;
}

Status heapify_down(Heap *heap, int i) {
    if(is_null(heap) || is_empty(heap) || i >= heap->size) return error;

    int l = return_left_child(i);
    int r = return_right_child(i);
    int key = i;

    if(heap->data != NULL) {
        if(l < heap->size && heap->data[l] > heap->data[key]) {
            key = l;
        } 

        if(r < heap->size && heap->data[r] > heap->data[key]) {
            key = r;
        }

        if(key != i) {
            swap_positions(heap, i, key);
            heapify_down(heap, key);
        } 

        return pass;
    }else {
        if(l < heap->size && heap->nodes[l].priority < heap->nodes[key].priority) {
            key = l;
        } 

        if(r < heap->size && heap->nodes[r].priority < heap->nodes[key].priority) {
            key = r;
        }

        if(key != i) {
            swap_positions(heap, i, key);
            heapify_down(heap, key);
        } 

        return pass;
    }
}

Status heapify_up(Heap *heap, int i) {
    if(is_null(heap) || is_empty(heap) || i >= heap->size) return error;
    
    int p = return_parent(i);

    if(heap->data != NULL) {
        if(p >= 0 && heap->data[i] > heap->data[p]) {
            swap_positions(heap, p, i);
            heapify_up(heap, p);
        }     
    }else {
        if(p >= 0 && heap->nodes[i].priority < heap->nodes[p].priority) {
            swap_positions(heap, p, i);
            heapify_up(heap, p);
        }
    }

    return pass;
}


// ========== Funções para o HeapSort ==========

Heap* create_simple_heap(int *array, int size) {
    Heap *new_heap = malloc(sizeof(Heap));
    if (is_null(new_heap)) return NULL;

    new_heap->capacity = size;
    new_heap->data = array;
    new_heap->size = size;

    new_heap->nodes = NULL;

    return new_heap;
}

Heap* build_simple_heap(int *array, int size) {
    Heap *heap = create_simple_heap(array, size);
    if (is_null(heap)) return NULL;

    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }

    return heap;
}

void heap_sort(int *array, int n) {
    if (is_null(array) || n <= 0) return;
    Heap *heap = build_simple_heap(array, n);
    
    for (int i = n - 1; i > 0; i--) {
        swap_positions(heap, 0, i);
        heap->size--;
        heapify_down(heap, 0);
    }

    free(heap);
}


// ========== Funções para o Algoritmo de Dijkstra ==========
Heap* create_dijkstra_heap(int vert_num) {
    Heap *new_heap = malloc(sizeof(Heap));
    if (is_null(new_heap)) return NULL;

    new_heap->capacity = vert_num;
    new_heap->size = 0;
    new_heap->data = NULL;
        
    new_heap->nodes = malloc(vert_num * sizeof(HeapNode));
    new_heap->vert_index = malloc(vert_num * sizeof(int));
    if (new_heap->vert_index == NULL || new_heap->nodes == NULL) {
        free(new_heap->vert_index);
        free(new_heap->nodes);
        free(new_heap);
        
        return NULL;   
    }

    for (int i = 0; i < vert_num; i++) {
        new_heap->vert_index[i] = -1;
    }
    
    return new_heap;
}

Heap* build_dijkstra_heap(int vert_num) {
    Heap *heap = create_dijkstra_heap(vert_num);
    if (is_null(heap)) return NULL;

    for (int i = 0; i < vert_num; i++) {
        heap->nodes[i].vert = i;
        heap->nodes[i].priority = INF;  
        heap->vert_index[i] = i;
    }

    heap->size = vert_num;
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

    return pass;
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

    int vert_index = heap->vert_index[vert];
    if(vert_index == -1){
        return error;
    }

    heap->nodes[vert_index].priority = new_priority;
    heapify_up(heap, vert_index);
    return pass;
}




