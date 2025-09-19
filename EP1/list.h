#ifndef LINKEDLIST_
#define LINKEDLIST_

#include <stdio.h>
#include <stdlib.h>



typedef struct List{ 
    int data;
    struct List *next;
} List;

typedef struct LinkedList {
    List *head;
    List *tail;
} LinkedList;




// funções públicas
LinkedList* create_list();
int first_node(LinkedList *L);
int list_is_empty(LinkedList *L);
void insert_node(LinkedList *L, int data);
void append_node(LinkedList *L, int data);
int delete_first_node(LinkedList *L);


void print_list(LinkedList *L);

#endif
