#ifndef _GRAPH_
#define _GRAPH_

#include "queue.h"
#include "stack.h"

typedef struct Graph {
    /* PREENCHA */
} Graph;

Graph*  create_graph(int n, int tipo);
int     add_edge(Graph *G, int u, int v);
int     remove_edge(Graph *G, int u, int v);
int*    bfs(Graph *G, int u);
int*    dfs(Graph *G, int u);
int     is_connected(Graph *G);

#endif
