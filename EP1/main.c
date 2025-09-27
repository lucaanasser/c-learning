#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main() {
    int operation;
    
    int value, n, t, u, v;
    Queue* Q;
    Stack* S;
    Graph* G;

    while (scanf("%d", &operation) == 1) {
        switch (operation) {
            /* FILA */
            case 1: // Cria fila vazia
                Q = create_queue();
                printf("Fila vazia criada.\n");

                break;
            case 2: // Insere um elemento na fila
                scanf("%d", &value);
                enqueue(Q, value);
                printf("%d inserido na fila.\n", value);

                break;

            case 3: // Remove e retorna primeiro elemento da fila, se houver
                printf("%d\n", dequeue(Q));

                break;

            case 4: // Retorna primeiro elemento da fila, se houver
                printf("%d\n", front(Q));

                break;


            case 5: // Verifica se a fila está vazia
                if(queue_is_empty(Q))   printf("A fila está vazia.\n");
                else                    printf("A fila não está vazia.\n");

                break;

            /* PILHA */
            case 6: // Cria pilha vazia
                S = create_stack();
                printf("Pilha vazia criada.\n");

                break;

            case 7: // Insere um elemento na pilha
                scanf("%d", &value);
                push(S, value);
                printf("%d inserido na pilha.\n", value);

                break;

            case 8: // Remove e retorna elemento do topo da pilha, se houver
                printf("%d\n", pop(S));

                break;

            case 9: // Exibe o primeiro elemento da pilha, se houver
                printf("%d\n", top(S));

                break;

            case 10: // Verifica se a pilha está vazia
                if(stack_is_empty(Q))   printf("A pilha está vazia.\n");
                else                    printf("A pilha não está vazia.\n");

                break;

            /* GRAFO */
            case 11: // Cria um grafo vazio com N vértices e tipo t
                scanf("%d %d", &n, &t);
                G = create_graph(n, t);

                break;

            case 12: // Se possível, adiciona aresta entre u e v no grafo G
                scanf("%d %d", &u, &v);
                if(add_edge(G, u, v))   printf("Aresta entre %d e %d adicionada!\n", u, v);
                else                    printf("Não foi possível adicionar aresta entre %d e %d.\n", u, v);


                break;

            case 13: // Se possível, remove aresta entre u e v do grafo G
                scanf("%d %d", &u, &v);
                if(remove_edge(G, u, v))   printf("Aresta entre %d e %d removida!\n", u, v);
                else                       printf("Não foi possível remover aresta entre %d e %d.\n", u, v);


                break;

            case 14: // Realiza BFS no grafo G a partir do vértice u e retorna o vetor de distâncias
                scanf("%d", &u);
                int* dist = bfs(G, u);

                for(int i=0; i<n; i++) printf("%d ", dist[i]);
                printf("\n");

                break;

            case 15: // Realiza BFS no grafo G a partir do vértice u e retorna o vetor de predecessores
                scanf("%d", &u);
                int* pred = dfs(G, u);

                for(int i=0; i<n; i++) printf("%d ", pred[i]);
                printf("\n");

                break;

            case 16: // Verifica se o grafo G é conexo
                if(is_connected(G)) printf("O grafo é conexo!\n");
                else                printf("O grafo não é conexo!\n");

                break;
        }
    }

    return 0;
}


