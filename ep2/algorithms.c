#include "algorithms.h"

// Função para o HeapSort

void heap_sort(int *array, int n) {
    if (array == NULL || n <= 0) return;
    Heap *heap = create_max_heap(array, n);
    
    for (int i = n - 1; i > 0; i--) {
        swap_positions(heap, 0, i);
        heap->size--;
        heapify_down(heap, 0);
    }

    free(heap);
}

// Funções para o algoritmo de Dijkstra

static void initialize_distances(int *dist, int vert_num, int s) {
  for(int i = 0; i < vert_num; i++) {
    dist[i] = INF;
  }
  dist[s] = 0;
}

static void process_list_neighbors(Graph *G, Priority_Queue *pq, int *dist, int u, int *visited) {
  List *current = G->adj_list[u]->head;
  
  while(current != NULL) {
    int v = current->data.vert;
    int weight = current->data.value;
    
    if(!visited[v] && dist[u] + weight < dist[v]) {
      int old_dist = dist[v];
      dist[v] = dist[u] + weight;
      
      if(old_dist == INF) {
        Edge edge = {v, dist[v]};
        pq_insert_sorted(pq, edge);
      } else {
        pq_decrease_priority(pq, v, dist[v]);
      }
    }
    
    current = current->next;
  }
}

static void process_matrix_neighbors(Graph *G, Priority_Queue *pq, int *dist, int u, int *visited) {
  for(int v = 0; v < G->vert_num; v++) {
    if(G->adj_matrix[u][v] != 0 && !visited[v]) {
      int weight = G->adj_matrix[u][v];
      
      if(dist[u] + weight < dist[v]) {
        int old_dist = dist[v];
        dist[v] = dist[u] + weight;
        
        if(old_dist == INF) {
          Edge edge = {v, dist[v]};
          pq_insert_sorted(pq, edge);
        } else {
          pq_decrease_priority(pq, v, dist[v]);
        }
      }
    }
  }
}

int* dijkstra_aux(Graph *G, int s, Priority_Queue_Type type) {
  if(graph_is_null(G)) return NULL;
  if(s < 0 || s >= G->vert_num) return NULL;
  
  int *dist = malloc(G->vert_num * sizeof(int));
  if(dist == NULL) return NULL;
  
  int *visited = calloc(G->vert_num, sizeof(int));
  if(visited == NULL) {
    free(dist);
    return NULL;
  }
  
  Priority_Queue *pq = create_pq(type, G->vert_num);
  if(pq_is_null(pq)) {
    free(dist);
    free(visited);
    return NULL;
  }
  
  initialize_distances(dist, G->vert_num, s);
  
  Edge s_edge = {s, 0};
  pq_insert_sorted(pq, s_edge);
  
  while(!pq_is_empty(pq)) {
    Edge min = pq_remove_min(pq);
    int u = min.vert;
    
    if(visited[u]) continue;
    visited[u] = 1;
    
    if(G->type == adj_list) {
      process_list_neighbors(G, pq, dist, u, visited);
    } else {
      process_matrix_neighbors(G, pq, dist, u, visited);
    }
  }
  
  free(visited);
  free_pq(pq);
  return dist;
}

int* dijkstra_heap(Graph *G, int s) {
    Priority_Queue_Type pq_type = heap;

    return dijkstra_aux(G, s, pq_type);
}

int* dijkstra_list(Graph *G, int s) {
    Priority_Queue_Type pq_type = linked_list;

    return dijkstra_aux(G, s, pq_type);
}