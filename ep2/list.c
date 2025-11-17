#include "list.h"
void free_list(LinkedList *L) {
    if (list_is_null(L)) return;

    List *current = L->head;
    while (current != NULL) {
        List *temp = current;
        current = current->next;
        free(temp);
    }

    free(L);
}

int list_is_null(LinkedList *L) {

    return (L == NULL);
}

int list_is_empty(LinkedList *L) {

    return (list_is_null(L) || L->head == NULL);
}

static List* add_node(int vert, int value) {
    List *new_node = malloc(sizeof(List));
    if (new_node == NULL) return NULL;

    new_node->data.vert = vert;
    new_node->data.value = value;
    new_node->next = NULL;
    
    return new_node;
}

static Edge remove_with(LinkedList *L, int target, int with_vert) {
    if (list_is_empty(L)) return (Edge){-1, -1};

    if ((with_vert && L->head->data.vert == target) || 
        (!with_vert && L->head->data.value == target)) return list_remove_min(L);

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

static int search_with(LinkedList *L, int target, int with_vert) {
    if(list_is_null(L)) return -1;
    
    List *aux = L->head;
    while(aux != NULL) {
        if ((with_vert && aux->data.vert == target) || 
            (!with_vert && aux->data.value == target)) return target;

        aux = aux->next;
    }
    
    return -1;
}

Edge list_return_min(LinkedList *L) {
    
    return(list_is_empty(L)) ? (Edge){-1, -1} : L->head->data;
}

LinkedList* create_list() {
    LinkedList *L = malloc(sizeof(LinkedList));
    if (list_is_null(L)) return NULL;
    
    L->head = NULL;
    L->tail = NULL;

    return L;
}

Status list_insert_node(LinkedList *L, Edge data) {
    if (list_is_null(L)) return error;
    
    List *insert = add_node(data.vert, data.value);
    if (insert == NULL) return error;

    insert->next = L->head;
    L->head = insert;

    if(L->tail == NULL) {
        L->tail = insert;
    }

    return success;
}

Status list_insert_sorted(LinkedList *L, Edge data) {
    if (list_is_null(L)) return error;

    if (L->head == NULL || L->head->data.value >= data.value) {
        return list_insert_node(L, data);
    }

    List *new_node = add_node(data.vert, data.value);
    if (new_node == NULL) return error;

    List *current = L->head;
    while (current->next != NULL && current->next->data.value < data.value) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    
    if (new_node->next == NULL) {
        L->tail = new_node;
    }

    return success;
}

Edge list_remove_min(LinkedList *L) {
    if(list_is_empty(L)) return (Edge){-1, -1};

    Edge show_first = list_return_min(L);

    List *temp = L->head;
    L->head = L->head->next;
    if(L->head == NULL) {
      L->tail = NULL;
    }

    free(temp);

    return show_first;
}

Edge list_remove_with_vert(LinkedList *L, int vert) {

    return remove_with(L, vert, 1);
}

Edge list_remove_with_value(LinkedList *L, int value) {

    return remove_with(L, value, 0);
}

int list_search_with_vert(LinkedList *L, int vert) {

    return search_with(L, vert, 1);
}

int list_search_with_value(LinkedList *L, int value) {

    return search_with(L, value, 0);
}

Status list_decrease_priority(LinkedList *L, int vert, int new_priority) {
    if(list_is_empty(L)) return error;

    Edge deleted = list_remove_with_vert(L, vert);
    if(deleted.vert == -1) return error;

    int old_priority = deleted.value;
    deleted.value = new_priority;
    
    if(list_insert_sorted(L, deleted) == error) {
        deleted.value = old_priority;
        list_insert_sorted(L, deleted);
        return error;
    }

    return success;
}

