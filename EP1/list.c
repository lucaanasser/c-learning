#include <stdio.h>
#include <stdlib.h>

typedef struct List{ 
    int data;
    struct List *next;
} List;

// decidi criar esse typedef para manter o append_node O(1) e ao mesmo tempo como void.
typedef struct LinkedList {
    List *head;
    List *tail;
} LinkedList;

List* add_node(int data) {
    List *new_node = malloc(sizeof(List));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}




LinkedList* create_list() {
    LinkedList *L = malloc(sizeof(LinkedList));
    L->head = NULL;
    L->tail = NULL;
    return L;
}

int first_node(LinkedList *L) {
    return (L->head == NULL) ? -1 : L->head->data;
}

int list_is_empty(LinkedList *L) {
    return (L->head == NULL) ? 1 : 0;
}

void insert_node(LinkedList *L, int data) {
    List *insert = add_node(data);
    insert->next = L->head;
    L->head = insert;
}

void append_node(LinkedList *L, int data){
    List *append = add_node(data);
    if(L->head == NULL){
        L->head = append;
        L->tail = append;
    } else {
        L->tail->next = append;
        L->tail = append;
    }
}

int delete_first_node(LinkedList *L) {
    if(L->head == NULL) {
        return -1;
    }
    int show_first = L->head->data;
    List *temp = L->head;
    L->head = L->head->next;
    if(L->head == NULL){
      L->tail = NULL;
    }
    free(temp);
    return show_first;
}

void print_list(LinkedList *L) {
    List *aux = L->head;
    while (aux != NULL) {
        printf("%d, ", aux->data);
        aux = aux->next;
    }
    printf("\n");
}

int main() {
    LinkedList *head = create_list();

    printf("%d \n", first_node(head)); 
    printf("%d \n", list_is_empty(head)); 

    insert_node(head, 20);
    insert_node(head, 10);
    append_node(head, 30);
    append_node(head, 40);

    print_list(head);
    
    printf("Deleted: %d\n", delete_first_node(head)); 
    print_list(head);

    return 0;
}