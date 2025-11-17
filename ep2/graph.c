#include "graph.h"

// Funcoes auxiliares gerais

static int check(Graph *G, int *u, int *v) {
    if(G == NULL) {
      printf("o grafo esta vazio");
      return 0;
    }
    if(v != NULL){
      if (*u < 0 || *u > (G->vert_num) - 1 || *v < 0 || *v > (G->vert_num) - 1) {
        printf("vertices fora dos limites (0 a %d)", G->vert_num - 1);
        return 0;
      }  
    }
    if (*u < 0 || *u > (G->vert_num) - 1) {
      printf("vertice fora dos limites (0 a %d)", G->vert_num - 1);
      return 0;
    }
    return 1;
}

//Fucoes auxiliares - grafo lista de adjacencia

static Graph* create_list_graph(Graph *new_graph) {
  int n = new_graph->vert_num;
  
  new_graph->adj_list = malloc(n * sizeof(LinkedList*));
  for(int i = 0; i < n; i++) {
    new_graph->adj_list[i] = create_list();
  }
  return new_graph;
}

static Status add_list_edge(Graph *G, int u, int v, int weight) {
  LinkedList *aux = G->adj_list[u];
  if(list_search_with_vert(aux, v) != -1) {
    printf("aresta ja existe");
    return error;
  }
  
  Edge edge_u = {v, weight};
  Edge edge_v = {u, weight};
  list_insert_node(G->adj_list[u], edge_u);
  list_insert_node(G->adj_list[v], edge_v);
  return success;
}

static Status remove_list_edge(Graph *G, int u, int v) {
  if(list_search_with_vert(G->adj_list[u], v) == -1) {
    printf("aresta nao existe");
    return error;
  }
  
  list_remove_with_vert(G->adj_list[u], v);
  list_remove_with_vert(G->adj_list[v], u);
  return success;
}

//Funcoes auxiliares - grafo matriz de adjacencia

static Graph* create_matrix_graph(Graph *new_graph) {
  int n = new_graph->vert_num;
  
  new_graph->adj_matrix = calloc(n, sizeof(int*));
  for(int i = 0; i < n; i++){
    new_graph->adj_matrix[i] = calloc(n, sizeof(int));
  }
  return new_graph;
}

static Status add_matrix_edge(Graph *G, int u, int v, int weight) {
  if (G->adj_matrix[u][v] != 0) {
    printf ("aresta ja existe");
    return error;
  }
  
  G->adj_matrix[u][v] = weight;
  G->adj_matrix[v][u] = weight;
  return success;
}

static Status remove_matrix_edge(Graph *G, int u, int v) {
  if (G->adj_matrix[u][v] == 0) {
    printf ("aresta nao existe");
    return error;
  }
  
  G->adj_matrix[u][v] = 0;
  G->adj_matrix[v][u] = 0;
  return success;
}

// Funções principais 

Graph* create_graph(Graph_Type type, int vert_num) {
  Graph *new_graph = malloc(sizeof(Graph));
  if(new_graph == NULL){
    return NULL;
  }
  new_graph->vert_num = vert_num;
  new_graph->type = type;

  return (type == adj_list) ? create_list_graph(new_graph) : create_matrix_graph(new_graph);
}

int add_edge(Graph *G, int u, int v, int weight) { 
  if (check(G, &u, &v) == 0){
    return error;
  }
  return (G->type == adj_list) ? add_list_edge(G, u, v, weight) : add_matrix_edge(G, u, v, weight);
}

int remove_edge(Graph *G, int u, int v) {
  if (check(G, &u, &v) == 0){
    return error;
  }
  
  return (G->type == adj_list) ? remove_list_edge(G, u, v) : remove_matrix_edge(G, u, v);
}

int get_edge_weight(Graph *G, int u, int v) {
  if (check(G, &u, &v) == 0){
    return -1;
  }
  
  if (G->type == adj_list) {
    // Buscar na lista de adjacência
    List *current = G->adj_list[u]->head;
    while (current != NULL) {
      if (current->data.vert == v) {
        return current->data.value;
      }
      current = current->next;
    }
    return -1; // Aresta não existe
  } else {
    // Matriz de adjacência
    if (G->adj_matrix[u][v] == 0) {
      return -1; // Aresta não existe
    }
    return G->adj_matrix[u][v];
  }
}