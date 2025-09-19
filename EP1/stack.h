#ifndef _STACK_
#define _STACK_

#include "list.h"

typedef struct Stack {
    int data;
    struct Stack *next; 
} Stack;

Stack*  create_stack();
void	  push(Stack *S, int novo_valor);
int	    pop(Stack *S);
int	    top(Stack *S);
int     stack_is_empty(Stack *S);

#endif
