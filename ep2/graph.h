#ifndef _GRAPH_
#define _GRAPH_

#include "list.h"

typedef struct Graph {
  int vert_num;
  LinkedList **adj_list;
} Graph;

Graph*  create_graph(int n);
int     add_edge(Graph *G, int u, int v);
int     remove_edge(Graph *G, int u, int v);

#endif
