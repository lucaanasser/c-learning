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

LinkedList* create_list();

int is_empty(LinkedList *L);
int is_null(LinkedList *L);
void free_list(LinkedList *L);
Edge first_node(LinkedList *L);                    

Status insert_node(LinkedList *L, int vert, int value); 
Status append_node(LinkedList *L, int vert, int value);
Status insert_sorted(LinkedList *L, int vert, int value);

Edge delete_first_node(LinkedList *L);
Edge delete_node_with_vert(LinkedList *L, int vert);
Edge delete_node_with_value(LinkedList *L, int value);

int search_node_with_vert(LinkedList *L, int vert);
int search_node_with_value(LinkedList *L, int value);



#endif
