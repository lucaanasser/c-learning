#include "list.h"
#include "stack.h"


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
  return var_pop;
}

int top(Stack *S){
  int var_top = first_node(S->stack);
  return var_top;
}

int stack_is_empty(Stack *S){
  int is_empty = list_is_empty(S->stack);
  return is_empty;
}
