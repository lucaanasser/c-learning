#ifndef _GRAPH_
#define _GRAPH_


typedef struct Graph {
  int vert_num;
  int type;
  union {
    LinkedList **adj_list;
    int **adj_matrix;
  };
} Graph;

Graph*  create_graph(int n, int tipo);
int     add_edge(Graph *G, int u, int v);
int     remove_edge(Graph *G, int u, int v);


#endif
