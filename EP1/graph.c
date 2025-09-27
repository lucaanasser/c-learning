#include "queue.h"
#include "stack.h"

typedef struct Graph {
  int vert_num;
  int type;
  union {
  LinkedList **adj_list;
  int **adj_matrix;
  };
} Graph;

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

int* bfs_0(Graph *G, int u, int *dist_list) {
  Queue *dist_queue = create_queue();
  dist_list[u] = 0;
  enqueue(dist_queue, u);
  
  while(queue_is_empty(dist_queue) != 1) { 
    int vert = dequeue(dist_queue);
    List *is_next = G->adj_list[vert]->head;
    
    while(is_next != NULL) {
        if(dist_list[is_next->data] == -1) {
          dist_list[is_next->data] = dist_list[vert] + 1;
          enqueue(dist_queue, is_next->data);
        }
      is_next = is_next->next;
    }
  }
  return dist_list;
}

int* dfs_0(Graph *G, int u, int *pred_list) {
  Queue *pred_stack = create_stack();
  push(pred_stack, u);
  pred_stack[u] = -2;
  
  while(queue_is_empty(pred_stack) != 1) { 
    int vert = pop(pred_stack);
    List *is_next = G->adj_list[vert]->head;
    
    while(is_next != NULL) {
        if(pred_list[is_next->data] == -1) {
          pred_list[is_next->data] = vert;
          push(pred_stack, is_next->data);
        }
      is_next = is_next->next;
    }
  }
  pred_stack[u] = -1;
  return pred_list;
}


is_connected_1(Graph *G) {
  
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

int* bfs_1(Graph *G, int u, int *dist_list) {
  Queue *dist_queue = create_queue();
  dist_list[u] = 0;
  enqueue(dist_queue, u);

  while(queue_is_empty(dist_queue) != 1) { 
    int vert = dequeue(dist_queue);
    
    for(int i = 0; i < G->vert_num; i++) {
      if(G->adj_matrix[vert][i] == 1 ) {
        if(dist_list[i] == -1){
          dist_list[i] = dist_list[vert] + 1;
          enqueue(dist_queue, i);
        }
      }
    }
  }
  
  return dist_list;
}

int* dfs_1(Graph *G, int u, int *pred_list) {
  Queue *pred_stack = create_stack();
  push(pred_stack, u);

  while(queue_is_empty(pred_stack) != 1) { 
    int vert = pop(pred_stack);
    
    for(int i = 0; i < G->vert_num; i++) {
      if(G->adj_matrix[vert][i] == 1 ) {
        if(pred_list[i] == -1){
          pred_list[i] = vert;
          push(pred_stack, i);
        }
      }
    }
  }
  
  return pred_list;
}

is_connected_1(Graph *G) {
  
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

int* bfs(Graph *G, int u) {
  if (check(G, &u, NULL) == 0){
    return NULL;
  }
  int *dist_list = malloc((G->vert_num) * sizeof(int));
  for(int i = 0; i < G->vert_num; i++){
    dist_list[i] = -1;
  }
  
  return (G->type == 1) ? bfs_1(G, u, dist_list) : bfs_0(G, u, dist_list);
}

int* dfs(Graph *G, int u) {
  if (check(G, &u, NULL) == 0){
    return NULL;
  }
  int *pre_list = malloc((G->vert_num) * sizeof(int));
  for(int i = 0; i < G->vert_num; i++){
    pred_list[i] = -1;
  }
  
  return (G->type == 1) ? dfs_1(G, u, pred_list) : dfs_0(G, u, pred_list);
}

int is_connected(Graph *G) {
  if (G == NULL){
    return 0;
  }
  
  return (G->type == 1) ? is_connected_1(G) : is_connected_0(G);
}
