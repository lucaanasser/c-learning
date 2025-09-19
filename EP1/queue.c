#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    LinkedList *queue;
} Queue;

Queue* create_queue() {
  Queue *new_queue = malloc(sizeof(Queue));
  new_queue->queue = create_list();
  return new_queue;
}

void enqueue(Queue *Q, int novo_valor) {
  append_node(Q->queue, novo_valor);
}

int dequeue(Queue *Q) {
  int var_dequeue = delete_first_node(Q->queue);
  return var_dequeue;
}

int front(Queue *Q) {
  int var_front = first_node(Q->queue);
  return var_front;
}

int queue_is_empty(Queue *Q) {
  int is_empty = list_is_empty(Q->queue);
  return is_empty;
}



void print_queue(Queue *Q) {
  print_list(Q->queue);
}


/*int main(){

    Queue *head = create_queue();
    
    int is_empty = queue_is_empty(head);
    printf("%d \n", is_empty);  

    enqueue(head, 10);
    enqueue(head, 20);
    enqueue(head, 30);

    is_empty = queue_is_empty(head);
    printf("%d \n", is_empty);  

    int var_front = front(head);
    printf("%d \n", var_front);

    int var_dequeue = dequeue(head);
    printf("%d \n", var_dequeue);
    
    var_front = front(head);
    printf("%d \n", var_front);

    print_queue(head);

}*/
