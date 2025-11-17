#ifndef _GRAPH_
#define _GRAPH_

#include "list.h"

typedef enum {
  adj_matrix,
  adj_list
}Graph_Type;

typedef struct Graph {
  Graph_Type type;
  int vert_num;
  
  union {
    LinkedList **adj_list;
    int **adj_matrix;
  };
} Graph;


Graph*  create_graph(Graph_Type type, int vert_num);

int     add_edge(Graph *G, int u, int v, int weight);
int     remove_edge(Graph *G, int u, int v);
int     get_edge_weight(Graph *G, int u, int v);

#endif
