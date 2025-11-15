#include "graph.h"

int check(Graph *G, int *u, int *v) {
    if (G == NULL) {
        printf("o grafo esta vazio");
        return 0;
    }
    if (v != NULL) {
        if (*u < 0 || *u >= G->vert_num || *v < 0 || *v >= G->vert_num) {
            printf("vertices fora dos limites (0 a %d)", G->vert_num - 1);
            return 0;
        }
    } else if (*u < 0 || *u >= G->vert_num) {
        printf("vertice fora dos limites (0 a %d)", G->vert_num - 1);
        return 0;
    }
    return 1;
}

Graph* create_graph(Graph *new_graph) {
    int n = new_graph->vert_num;
    new_graph->adj_list = malloc(n * sizeof(LinkedList*));
    for (int i = 0; i < n; i++) {
        new_graph->adj_list[i] = create_list();
    }
    return new_graph;
}

int add_edge(Graph *G, int u, int v) {
    if (check(G, &u, &v) == 0) {
        return 0;
    }

    LinkedList *aux = G->adj_list[u];
    if (search_node_with_value(aux, v) != -1) {
        printf("aresta ja existe");
        return 0;
    }

    insert_node(G->adj_list[u], v);
    insert_node(G->adj_list[v], u);
    return 1;
}

int remove_edge(Graph *G, int u, int v) {
    if (check(G, &u, &v) == 0) {
        return 0;
    }

    if (search_node_with_value(G->adj_list[u], v) == -1) {
        printf("aresta nao existe");
        return 0;
    }

    delete_node_with_value(G->adj_list[u], v);
    delete_node_with_value(G->adj_list[v], u);
    return 1;
}

Graph* create_graph_main(int n) {
    Graph *new_graph = malloc(sizeof(Graph));
    if (new_graph == NULL) {
        return NULL;
    }
    new_graph->vert_num = n;
    return create_graph(new_graph);
}
