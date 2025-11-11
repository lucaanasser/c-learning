#include "graph.h"

// Funcoes auxiliares gerais
int check(Graph *G, int *u, int *v) {
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

int* create_neg1_array(int size) {
    int *array = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        array[i] = -1;
    }
    return array;
}


//Fucoes auxiliares - Grafo tipo 0 - lista de adjacencia
Graph* create_graph_0(Graph *new_graph) {
  int n = new_graph->vert_num;
  
  new_graph->adj_list = malloc(n * sizeof(LinkedList*));
  for(int i = 0; i < n; i++) {
    new_graph->adj_list[i] = create_list();
  }
  return new_graph;
}

int add_edge_0(Graph *G, int u, int v) {
  LinkedList *aux = G->adj_list[u];
  if(search_node_with_value(aux, v) != -1) {
    printf("aresta ja existe");
    return 0;
  }
  
  insert_node(G->adj_list[u], v);
  insert_node(G->adj_list[v], u);
  return 1;
}

int remove_edge_0(Graph *G, int u, int v) {
  if(search_node_with_value(G->adj_list[u], v) == -1) {
    printf("aresta nao existe");
    return 0;
  }
  
  delete_node_with_value(G->adj_list[u], v);
  delete_node_with_value(G->adj_list[v], u);
  return 1;
}

  

//Funcoes auxiliares - Grafo tipo 1 - matriz de adjacencia
Graph* create_graph_1(Graph *new_graph) {
  int n = new_graph->vert_num;
  
  new_graph->adj_matrix = calloc(n, sizeof(int*));
  for(int i = 0; i < n; i++){
    new_graph->adj_matrix[i] = calloc(n, sizeof(int));
  }
  return new_graph;
}

int add_edge_1(Graph *G, int u, int v) {
  if (G->adj_matrix[u][v] == 1) {
    printf ("aresta ja existe");
    return 0;
  }
  
  G->adj_matrix[u][v] = 1;
  G->adj_matrix[v][u] = 1;
  return 1;
}

int remove_edge_1(Graph *G, int u, int v) {
  if (G->adj_matrix[u][v] == 0) {
    printf ("aresta nao existe");
    return 0;
  }
  
  G->adj_matrix[u][v] = 0;
  G->adj_matrix[v][u] = 0;
  return 1;
}


// Funcoes obrigatorias 
Graph* create_graph(int n, int tipo) {
  Graph *new_graph = malloc(sizeof(Graph));
  if(new_graph == NULL){
    return NULL;
  }
  new_graph->vert_num = n;
  new_graph->type = tipo;

  return (tipo == 1) ? create_graph_1(new_graph) : create_graph_0(new_graph);
}

int add_edge(Graph *G, int u, int v) { 
  if (check(G, &u, &v) == 0){
    return 0;
  }
  return (G->type == 1) ? add_edge_1(G, u, v) : add_edge_0(G, u, v);
}

int remove_edge(Graph *G, int u, int v) {
  if (check(G, &u, &v) == 0){
    return 0;
  }
  
  return (G->type == 1) ? remove_edge_1(G, u, v) : remove_edge_0(G, u, v);
}
