#include <stdio.h>
#include <stdlib.h>


typedef struct Heap {
    int *data;      
    int size;     
    int capacity;  
} Heap;


Heap* create_heap(int capacity) {
    Heap *new_heap = malloc(sizeof(Heap));
    new_heap->data = malloc(sizeof(int) * capacity);
    new_heap->size = 0;
    new_heap->capacity = capacity;

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


Heap* heapify_down(Heap *heap, int i) {
    int l = return_left_child(i);
    int r = return_right_child(i);
    int largest = i;

    if(l <= heap->size - 1 && heap->data[l] > heap->data[largest]) {
        largest = l;
    } 

    if(r <= heap->size - 1 && heap->data[r] > largest) {
        largest = r;
    }

    if(largest != i) {
        change_positions(heap->data, i, largest);
        heapify_down(heap, largest);
    } 

    return heap;

}


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

void replace_max(Heap *heap) {
   int max_value = heap->data[0];
   heap->data[0] = heap->[heap->size];
   heap->data[heap->size] = max_value;
   heap->size--;
}

Heap* build_heap(int array[], int size) {
    Heap *heap = create_heap(size);
    heap->size = size;   
    for(int i = 0; i < size; i++) {
        heap->data[i] = array[i];
    }


    for(int i = (size/2) - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }
    
    return heap;
}


Heap* heap_sort(Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        replace_max(heap);
        heapify_down(heap->data, 0);
    }

    return heap;
}


int main(void) {
    create_heap(1);
}


