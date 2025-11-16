#include "list.h"

int is_null(LinkedList *L) {

    return (L == NULL);
}

int is_empty(LinkedList *L) {

    return (is_null(L) || L->head == NULL);
}

void free_list(LinkedList *L) {
    if (is_null(L)) return;

    List *current = L->head;
    while (current != NULL) {
        List *temp = current;
        current = current->next;
        free(temp);
    }

    free(L);
}

Edge first_node(LinkedList *L) {
    
    return(is_empty(L)) ? (Edge){-1, -1} : L->head->data;
}

LinkedList* create_list() {
    LinkedList *L = malloc(sizeof(LinkedList));
    if (is_null(L)) return NULL;
    
    L->head = NULL;
    L->tail = NULL;

    return L;
}

List* add_node(int vert, int value) {
    List *new_node = malloc(sizeof(List));
    if (is_null(new_node)) return NULL;

    new_node->data.vert = vert;
    new_node->data.value = value;
    new_node->next = NULL;
    
    return new_node;
}

Status insert_node(LinkedList *L, int vert, int value) {
    if (is_null(L)) return error;
    
    List *insert = add_node(vert, value);
    if (is_null(insert)) return error;

    insert->next = L->head;
    L->head = insert;

    if(L->tail == NULL) {
        L->tail = insert;
    }

    return success;
}

Status append_node(LinkedList *L, int vert, int value) {
    if (is_null(L)) return error;
    
    if(L->head == NULL) {
        insert_node(L, vert, value);

        return success;
    }

    List *append = add_node(vert, value);
    if (is_null(append)) return error;

    L->tail->next = append;
    L->tail = append;
        
    return success;
}

Status insert_sorted(LinkedList *L, int vert, int value) {
    if (is_null(L)) return error;

    if (L->head == NULL || L->head->data.value >= value) {
        insert_node(L, vert, value);

        return success;
    }

    List *new_node = add_node(vert, value);
    if (is_null(new_node)) return error;

    List *current = L->head;
    while (current->next != NULL && current->next->data.value < value) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    
    if (new_node->next == NULL) {
        L->tail = new_node;
    }

    return success;
}

Edge delete_first_node(LinkedList *L) {
    if(is_null(L) || is_empty(L)) return (Edge){-1, -1};

    Edge show_first = first_node(L);

    List *temp = L->head;
    L->head = L->head->next;
    if(L->head == NULL) {
      L->tail = NULL;
    }

    free(temp);

    return show_first;
}

Edge delete_node_with(LinkedList *L, int target, int with_vert) {
    if (is_null(L) || is_empty(L)) return (Edge){-1, -1};

    if ((with_vert && L->head->data.vert == target) || 
        (!with_vert && L->head->data.value == target)) return delete_first_node(L);

    List *aux = L->head;
    while (aux->next != NULL) {
        int match = (with_vert && aux->next->data.vert == target) || 
            (!with_vert && aux->next->data.value == target);
        
        if (match) {
            List *node_to_delete = aux->next;
            Edge deleted_data = node_to_delete->data;
            
            aux->next = node_to_delete->next;
            if (node_to_delete == L->tail) {
                L->tail = aux;
            }
            
            free(node_to_delete);

            return deleted_data;
        }

        aux = aux->next;
    }

    return (Edge){-1, -1};
}

Edge delete_node_with_vert(LinkedList *L, int vert) {

    return delete_node_with(L, vert, 1);
}

Edge delete_node_with_value(LinkedList *L, int value) {

    return delete_node_with(L, value, 0);
}

int search_node_with(LinkedList *L, int target, int with_vert) {
    if(is_null(L)) return -1;
    
    List *aux = L->head;
    while(aux != NULL) {
        if ((with_vert && aux->data.vert == target) || 
            (!with_vert && aux->data.value == target)) return target;

        aux = aux->next;
    }
    
    return -1;
}

int search_node_with_vert(LinkedList *L, int vert) {

    return search_node_with(L, vert, 1);
}

int search_node_with_value(LinkedList *L, int value) {

    return search_node_with(L, value, 0);
}

