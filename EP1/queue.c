#include "list.h"
#include "queue.h"


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
