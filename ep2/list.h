#ifndef LINKEDLIST_
#define LINKEDLIST_

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    success = 0,
    error = -1
} Status;

typedef struct Edge {
    int vert;
    int value;
} Edge;

typedef struct List{ 
    Edge data;
    struct List *next;
} List;

typedef struct LinkedList {
    List *head;
    List *tail;
} LinkedList;


void free_list(LinkedList *L);

int list_is_empty(LinkedList *L);
int list_is_null(LinkedList *L);

Edge list_return_min(LinkedList *L);      

LinkedList* create_list();              

Status list_insert_node(LinkedList *L, Edge data);
Status list_insert_sorted(LinkedList *L, Edge data);

Edge list_remove_min(LinkedList *L);
Edge list_remove_with_vert(LinkedList *L, int vert);
Edge list_remove_with_value(LinkedList *L, int value);

Status list_decrease_priority(LinkedList *L, int vert, int new_priority);

int list_search_with_vert(LinkedList *L, int vert);
int list_search_with_value(LinkedList *L, int value);


#endif
