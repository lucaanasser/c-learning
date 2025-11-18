#ifndef _ALGORITHMS_
#define _ALGORITHMS_

#include "graph.h"
#include "priority_queue.h"

int* dijkstra_heap(Graph *G, int s);
int* dijkstra_list(Graph *G, int s);
int* dijkstra_aux(Graph *G, int s, Priority_Queue_Type type);

#endif
