#ifndef _GRAPH_
#define _GRAPH_

#include "list.h"
#define INF 42424242

typedef enum {
  adj_matrix,
  adj_list
} Graph_Type;

typedef struct Graph {
  Graph_Type type;
  int vert_num;
  
  union {
    LinkedList **adj_list;
    int **adj_matrix;
  };
} Graph;

void free_graph(Graph *G);

int graph_is_null(Graph *G);
int graph_is_empty(Graph *G);
int graph_is_full(Graph *G);

Graph* create_graph(Graph_Type type, int vert_num);

Status add_edge(Graph *G, int u, int v, int weight);
Status remove_edge(Graph *G, int u, int v);
int get_edge_weight(Graph *G, int u, int v);

#endif
