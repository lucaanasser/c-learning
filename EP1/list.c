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
    return(L->head == NULL) ? -1 : L->head->data;
}

int list_is_empty(LinkedList *L) {
    return first_node(L) == -1;
}

void insert_node(LinkedList *L, int data) {
    List *insert = add_node(data);
    insert->next = L->head;
    L->head = insert;
    if(L->tail == NULL) {
        L->tail = insert;
    }
}

void append_node(LinkedList *L, int data){
    if(L->head == NULL) {
        insert_node(L, data);  
    } else {
        List *append = add_node(data);
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
    if(L->head == NULL) {
      L->tail = NULL;
    }

    free(temp);
    return show_first;
}

int delete_node_with_value(LinkedList *L, int value) {
    if (L->head == NULL){
      return -1;
    } 
    if (L->head->data == value) {
        return delete_first_node(L);
    }
    
    List *aux = L->head;
    while (aux->next != NULL) {
        if (aux->next->data == value) {
            List *node_to_delete = aux->next;
            aux->next = node_to_delete->next;
            if (node_to_delete == L->tail) {
                L->tail = aux;
            }
            free(node_to_delete);
            return value;
        }
        aux = aux->next;
    }
    return -1;
}

int search_node_with_value(LinkedList *L, int value){
    if(L == NULL){
      return -1;
    }
    
    List *aux = L->head;
    while(aux != NULL) {
      if(aux->data == value) {
        return value; 
      }
      aux = aux->next;
    }
    
    return -1;
}

void print_list(LinkedList *L) {
    List *aux = L->head;
    while(aux != NULL) {
        printf("%d, ", aux->data);
        aux = aux->next;
    }
    printf("\n");
}

/*int main() {
    LinkedList *head = create_list();

    printf("%d \n", first_node(head)); 
    printf("%d \n", list_is_empty(head)); 

    insert_node(head, 20);
    insert_node(head, 10);
    append_node(head, 30);
    append_node(head, 40);

    print_list(head);
    
    printf("numero deletado: %d\n", delete_first_node(head)); 
    print_list(head);

    return 0;
}*/