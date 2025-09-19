#include "list.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Stack {
    LinkedList *stack;
} Stack;

Stack* create_stack() {
    Stack *new_stack = malloc(sizeof(Stack));
    new_stack->stack = create_list();
    return new_stack;
}
void push(Stack *S, int novo_valor){
  
  insert_node(S->stack, novo_valor);
}

int pop(Stack *S){
  int var_pop = delete_first_node(S->stack);
  return pop;
}

int top(Stack *S){
  int var_top = first_node(S->stack);
  return var_top;
}

int stack_is_empty(Stack *S){
  int is_empty = list_is_empty(S->stack);
  return is_empty;
}


void print_stack(Stack *S){
    print_list(S->stack);
}

/*int main(){

    Stack *head = create_stack();


    push(head, 10);
    push(head, 20);
    push(head, 30);

    int var_top = top(head);

    printf("%d \n", var_top);

    int var_pop = pop(head);
    var_top = top(head);
    printf("%d \n", var_top);


    print_stack(head);

}*/