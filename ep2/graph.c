#include "graph.h"

void free_graph(Graph *G) {
  if(graph_is_null(G)) return;
  
  if(G->type == adj_list) {
    if(G->adj_list != NULL) {
      for(int i = 0; i < G->vert_num; i++) {
        free_list(G->adj_list[i]);
      }
      free(G->adj_list);
    }
  } else {
    if(G->adj_matrix != NULL) {
      for(int i = 0; i < G->vert_num; i++) {
        free(G->adj_matrix[i]);
      }
      free(G->adj_matrix);
    }
  }
  
  free(G);
}

int graph_is_null(Graph *G) {
  return (G == NULL);
}

int graph_is_empty(Graph *G) {
  if(graph_is_null(G)) return 1;
  
  if(G->type == adj_list) {
    for(int i = 0; i < G->vert_num; i++) {
      if(!list_is_empty(G->adj_list[i])) return 0;
    }
  } else {
    for(int i = 0; i < G->vert_num; i++) {
      for(int j = 0; j < G->vert_num; j++) {
        if(G->adj_matrix[i][j] != 0) return 0;
      }
    }
  }
  
  return 1;
}

int graph_is_full(Graph *G) {
  (void)G;
  return 0;
}

static int check_edge(Graph *G, int u, int v, int weight) {
  if(graph_is_null(G)) return 0;
  if(u < 0 || u > (G->vert_num) - 1 || v < 0 || v > (G->vert_num) - 1) return 0;
  if(weight < 0 || weight >= INF) return 0;
  
  return 1;
}

static Graph* create_list_graph(Graph *new_graph) {
  new_graph->adj_list = malloc(new_graph->vert_num * sizeof(LinkedList*));
  if(new_graph->adj_list == NULL) {
    free(new_graph);
    return NULL;
  }
  
  for(int i = 0; i < new_graph->vert_num; i++) {
    new_graph->adj_list[i] = create_list();
    if(new_graph->adj_list[i] == NULL) {
      for(int j = 0; j < i; j++) {
        free_list(new_graph->adj_list[j]);
      }
      free(new_graph->adj_list);
      free(new_graph);
      return NULL;
    }
  }
  
  return new_graph;
}

static Graph* create_matrix_graph(Graph *new_graph) {
  new_graph->adj_matrix = calloc(new_graph->vert_num, sizeof(int*));
  if(new_graph->adj_matrix == NULL) {
    free(new_graph);
    return NULL;
  }
  
  for(int i = 0; i < new_graph->vert_num; i++) {
    new_graph->adj_matrix[i] = calloc(new_graph->vert_num, sizeof(int));
    if(new_graph->adj_matrix[i] == NULL) {
      for(int j = 0; j < i; j++) {
        free(new_graph->adj_matrix[j]);
      }
      free(new_graph->adj_matrix);
      free(new_graph);
      return NULL;
    }
  }
  
  return new_graph;
}

static Status add_list_edge(Graph *G, int u, int v, int weight) {
  if(list_search_with_vert(G->adj_list[u], v) != -1) return error;
  
  Edge edge_u = {v, weight};
  Edge edge_v = {u, weight};
  
  if(list_insert_node(G->adj_list[u], edge_u) == error) return error;
  if(list_insert_node(G->adj_list[v], edge_v) == error) {
    list_remove_with_vert(G->adj_list[u], v);
    return error;
  }
  
  return success;
}

static Status add_matrix_edge(Graph *G, int u, int v, int weight) {
  if(G->adj_matrix[u][v] != 0) return error;
  
  G->adj_matrix[u][v] = weight;
  G->adj_matrix[v][u] = weight;
  
  return success;
}

static Status remove_list_edge(Graph *G, int u, int v) {
  if(list_search_with_vert(G->adj_list[u], v) == -1) return error;
  
  list_remove_with_vert(G->adj_list[u], v);
  list_remove_with_vert(G->adj_list[v], u);
  
  return success;
}

static Status remove_matrix_edge(Graph *G, int u, int v) {
  if(G->adj_matrix[u][v] == 0) return error;
  
  G->adj_matrix[u][v] = 0;
  G->adj_matrix[v][u] = 0;
  
  return success;
}

static int get_list_edge_weight(Graph *G, int u, int v) {
  List *current = G->adj_list[u]->head;
  
  while(current != NULL) {
    if(current->data.vert == v) return current->data.value;
    current = current->next;
  }
  
  return -1;
}

static int get_matrix_edge_weight(Graph *G, int u, int v) {
  if(G->adj_matrix[u][v] == 0) return -1;
  
  return G->adj_matrix[u][v];
}

Graph* create_graph(Graph_Type type, int vert_num) {
  Graph *new_graph = malloc(sizeof(Graph));
  if(graph_is_null(new_graph)) return NULL;
  
  new_graph->vert_num = vert_num;
  new_graph->type = type;
  
  return (type == adj_list) ? create_list_graph(new_graph) : create_matrix_graph(new_graph);
}

Status add_edge(Graph *G, int u, int v, int weight) {
  if(graph_is_null(G)) return error;
  if(!check_edge(G, u, v, weight)) return error;
  if(graph_is_full(G)) return error;
  
  return (G->type == adj_list) ? add_list_edge(G, u, v, weight) : add_matrix_edge(G, u, v, weight);
}

Status remove_edge(Graph *G, int u, int v) {
  if(graph_is_null(G) || graph_is_empty(G)) return error;
  if(!check_edge(G, u, v, 0)) return error;
  
  return (G->type == adj_list) ? remove_list_edge(G, u, v) : remove_matrix_edge(G, u, v);
}

int get_edge_weight(Graph *G, int u, int v) {
  if(graph_is_null(G) || graph_is_empty(G)) return -1;
  if(!check_edge(G, u, v, 0)) return -1;
  
  return (G->type == adj_list) ? get_list_edge_weight(G, u, v) : get_matrix_edge_weight(G, u, v);
}