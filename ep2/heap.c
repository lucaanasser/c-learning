#include "heap.h"

Heap* create_heap(int capacity, HeapType type) {
    Heap *new_heap = malloc(sizeof(Heap));
    if (new_heap == NULL) return NULL;

    new_heap->data = NULL;
    new_heap->size = 0;
    new_heap->capacity = capacity;
    new_heap->type = type;

    return new_heap;
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

void change_positions(int array[], int i, int j) {
    int temp = array[i];
    array[i] = array[j]; 
    array[j] = temp;
}

Heap* heapify_down(Heap *heap, int i, HeapType type) {
    int l = return_left_child(i);
    int r = return_right_child(i);
    int key = i;

    if(type == max) {
        if(l < heap->size && heap->data[l] > heap->data[key]) {
            key = l;
        } 

        if(r < heap->size && heap->data[r] > heap->data[key]) {
            key = r;
        }

        if(key != i) {
            change_positions(heap->data, i, key);
            heapify_down(heap, key, type);
        } 

        return heap;
    } else {
        if(l < heap->size && heap->data[l] < heap->data[key]) {
            key = l;
        } 

        if(r < heap->size && heap->data[r] < heap->data[key]) {
            key = r;
        }

        if(key != i) {
            change_positions(heap->data, i, key);
            heapify_down(heap, key, type);
        } 

        return heap;
    }
}

Heap* build_heap(int *array, int size, HeapType type) {
    if(type == max) {
        Heap *heap = create_heap(size, type);
        heap->size = size;
        heap->data = array;

        for(int i = (size/2) - 1; i >= 0; i--) {
            heapify_down(heap, i, type);
        }
        
        return heap;
    } else {
        Heap *heap = create_heap(size, type);
        heap->size = size;
        heap->data = array;

        for(int i = (size/2) - 1; i >= 0; i--) {
            heapify_down(heap, i, type);
        }
        
        return heap;
    }
}

void heap_sort(int *array, int size) {
    HeapType type = max;
    Heap *heap = build_heap(array, size, type);
    
    for (int i = size - 1; i > 0; i--) {
        change_positions(heap->data, 0, i);
        heap->size--;
        heapify_down(heap, 0, type);
    }


    free(heap);
}



/*
Heap* heapify_up(Heap *heap, int i) {
    int p = return_parent(i);

    if(p >= 0 && heap->data[i] > heap->data[p]) {
        change_positions(heap->data, p, i);
        heapify_up(heap, p);   
    } 

    return heap;
}

Heap* end_insert(Heap *heap, int value) {
    if(heap->capacity <= heap->size) {
        int *temp_arr = (int *)realloc(heap->data, (heap->capacity * 2) * sizeof(int));
        
        if (temp_arr == NULL) {
            free(heap->data);

            return NULL; 
        }else {
            heap->data = temp_arr; 
        }

        heap->capacity = heap->capacity * 2;
    }

    heap->data[heap->size] = value;
    heap->size++;
    heapify_up(heap, heap->size);

    return heap;
}

int remove_max(Heap *heap) {
   int max_value = heap->data[0];
   heap->data[0] = heap->[heap->size];
   heap->size--;
   heapify_down(heap, 0);

   return max_value;
}

*/








