#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

// Estatísticas globais
int total_tests = 0;
int passed_tests = 0;
int failed_tests = 0;

// Cores para terminal
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Macro para testes com valor esperado e obtido
#define TEST_INT(desc, expected, actual) \
    do { \
        total_tests++; \
        printf("  %-50s", desc); \
        if ((expected) == (actual)) { \
            printf(GREEN "✓ PASS" RESET " | Esperado: %d, Obtido: %d\n", expected, actual); \
            passed_tests++; \
        } else { \
            printf(RED "✗ FAIL" RESET " | Esperado: %d, Obtido: %d\n", expected, actual); \
            failed_tests++; \
        } \
    } while(0)

#define TEST_BOOL(desc, expected, actual) \
    do { \
        total_tests++; \
        printf("  %-50s", desc); \
        if ((expected) == (actual)) { \
            printf(GREEN "✓ PASS" RESET " | Esperado: %s, Obtido: %s\n", \
                   (expected) ? "true" : "false", (actual) ? "true" : "false"); \
            passed_tests++; \
        } else { \
            printf(RED "✗ FAIL" RESET " | Esperado: %s, Obtido: %s\n", \
                   (expected) ? "true" : "false", (actual) ? "true" : "false"); \
            failed_tests++; \
        } \
    } while(0)

#define TEST_POINTER(desc, expected_null, actual) \
    do { \
        total_tests++; \
        printf("  %-50s", desc); \
        int is_null = ((actual) == NULL); \
        if ((expected_null) == is_null) { \
            printf(GREEN "✓ PASS" RESET " | Ponteiro %s como esperado\n", \
                   is_null ? "NULL" : "válido"); \
            passed_tests++; \
        } else { \
            printf(RED "✗ FAIL" RESET " | Esperado ponteiro %s, obtido %s\n", \
                   (expected_null) ? "NULL" : "válido", is_null ? "NULL" : "válido"); \
            failed_tests++; \
        } \
    } while(0)

// Função para imprimir cabeçalho de seção
void print_section_header(const char *title) {
    int len = strlen(title);
    printf("\n" BOLD CYAN "╔");
    for(int i = 0; i < len + 4; i++) printf("═");
    printf("╗\n║  %s  ║\n╚", title);
    for(int i = 0; i < len + 4; i++) printf("═");
    printf("╝" RESET "\n\n");
}

// Função para imprimir array (para debug de BFS/DFS)
void print_array(const char *title, int *arr, int n) {
    printf("    %s" YELLOW ": [", title);
    for(int i = 0; i < n; i++) {
        if (i > 0) printf(", ");
        printf("%d", arr[i]);
    }
    printf("]" RESET "\n");
}

// Função para verificar se dois arrays são iguais
int arrays_equal(int *arr1, int *arr2, int n) {
    if (arr1 == NULL || arr2 == NULL) return 0;
    for(int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }
    return 1;
}

/* ================= TESTES DE LISTA LIGADA ================= */
static void test_list_basic() {
    printf(BOLD "Testes Básicos de Lista:\n" RESET);
    
    LinkedList *L = create_list();
    TEST_POINTER("Criação de lista", 0, L);
    TEST_BOOL("Lista nova está vazia", 1, list_is_empty(L));
    TEST_INT("Primeiro nó de lista vazia", -1, first_node(L));

    // Inserção no início
    insert_node(L, 10);
    TEST_BOOL("Lista não vazia após inserção", 0, list_is_empty(L));
    TEST_INT("Primeiro nó após inserção", 10, first_node(L));

    // Append no final
    append_node(L, 20);
    TEST_INT("Head mantém valor após append", 10, first_node(L));
    TEST_INT("Buscar valor 20", 20, search_node_with_value(L, 20));

    // Múltiplas inserções
    insert_node(L, 5);  // [5, 10, 20]
    append_node(L, 25); // [5, 10, 20, 25]
    TEST_INT("Head após múltiplas inserções", 5, first_node(L));
    TEST_INT("Buscar valor do meio", 10, search_node_with_value(L, 10));

    // Remoções
    int deleted = delete_first_node(L);
    TEST_INT("Valor removido do início", 5, deleted);
    TEST_INT("Novo head após remoção", 10, first_node(L));

    int del_value = delete_node_with_value(L, 20);
    TEST_INT("Remoção por valor", 20, del_value);
    TEST_INT("Buscar valor removido", -1, search_node_with_value(L, 20));
}

static void test_list_edge_cases() {
    printf(BOLD "\nTestes de Casos Extremos - Lista:\n" RESET);
    
    LinkedList *L = create_list();
    
    // Operações em lista vazia
    TEST_INT("Deletar primeiro de lista vazia", -1, delete_first_node(L));
    TEST_INT("Deletar por valor em lista vazia", -1, delete_node_with_value(L, 5));
    TEST_INT("Buscar em lista vazia", -1, search_node_with_value(L, 5));
    
    // Lista com um elemento
    append_node(L, 42);
    TEST_INT("Buscar único elemento", 42, search_node_with_value(L, 42));
    int single_del = delete_node_with_value(L, 42);
    TEST_INT("Deletar único elemento", 42, single_del);
    TEST_BOOL("Lista vazia após deletar único", 1, list_is_empty(L));
    
    // Lista grande (stress test)
    for(int i = 0; i < 100; i++) {
        append_node(L, i);
    }
    TEST_INT("Primeiro de lista grande", 0, first_node(L));
    TEST_INT("Buscar meio da lista grande", 50, search_node_with_value(L, 50));
    TEST_INT("Buscar final da lista grande", 99, search_node_with_value(L, 99));
    
    // Deletar do meio
    TEST_INT("Deletar do meio", 50, delete_node_with_value(L, 50));
    TEST_INT("Confirmar remoção do meio", -1, search_node_with_value(L, 50));
    
    // Deletar inexistente
    TEST_INT("Deletar valor inexistente", -1, delete_node_with_value(L, 200));
}

static void test_list_null_pointers() {
    printf(BOLD "\nTestes de Ponteiros Nulos - Lista:\n" RESET);
    
    // Testes com ponteiro NULL
    TEST_INT("Buscar com lista NULL", -1, search_node_with_value(NULL, 5));
    // Note: outras funções podem crashar com NULL, então testamos apenas search
}

/* ================= TESTES DE PILHA ================= */
static void test_stack_basic() {
    printf(BOLD "Testes Básicos de Pilha:\n" RESET);
    
    Stack *S = create_stack();
    TEST_POINTER("Criação de pilha", 0, S);
    TEST_BOOL("Pilha nova está vazia", 1, stack_is_empty(S));
    
    // Push e verificações
    push(S, 5);
    TEST_BOOL("Pilha não vazia após push", 0, stack_is_empty(S));
    TEST_INT("Top após primeiro push", 5, top(S));
    
    push(S, 7);
    TEST_INT("Top após segundo push", 7, top(S));
    
    push(S, 9);
    TEST_INT("Top após terceiro push", 9, top(S));
    
    // Pop e verificações
    int popped = pop(S);
    TEST_INT("Pop retorna último elemento", 9, popped);
    TEST_INT("Top após pop", 7, top(S));
    
    pop(S);
    TEST_INT("Top após segundo pop", 5, top(S));
    
    pop(S);
    TEST_BOOL("Pilha vazia após todos os pops", 1, stack_is_empty(S));
}

static void test_stack_edge_cases() {
    printf(BOLD "\nTestes de Casos Extremos - Pilha:\n" RESET);
    
    Stack *S = create_stack();
    
    // Operações em pilha vazia
    TEST_INT("Pop de pilha vazia", -1, pop(S));
    TEST_INT("Top de pilha vazia", -1, top(S));
    
    // Um elemento
    push(S, 42);
    TEST_INT("Top com um elemento", 42, top(S));
    TEST_INT("Pop único elemento", 42, pop(S));
    TEST_BOOL("Vazia após pop único", 1, stack_is_empty(S));
    
    // Stress test - muitos elementos
    for(int i = 0; i < 1000; i++) {
        push(S, i);
    }
    TEST_INT("Top de pilha grande", 999, top(S));
    
    // Pop sequencial verificando ordem LIFO
    for(int i = 999; i >= 997; i--) {
        int val = pop(S);
        if (i == 999) TEST_INT("Pop ordem LIFO (999)", i, val);
        else if (i == 998) TEST_INT("Pop ordem LIFO (998)", i, val);
        else if (i == 997) TEST_INT("Pop ordem LIFO (997)", i, val);
    }
}

static void test_stack_alternating() {
    printf(BOLD "\nTestes de Operações Alternadas - Pilha:\n" RESET);
    
    Stack *S = create_stack();
    
    // Padrão push-pop alternado
    push(S, 1);
    TEST_INT("Push-pop alternado 1", 1, pop(S));
    TEST_BOOL("Vazia após ciclo", 1, stack_is_empty(S));
    
    push(S, 2);
    push(S, 3);
    TEST_INT("Dois pushes, primeiro pop", 3, pop(S));
    push(S, 4);
    TEST_INT("Push após pop", 4, top(S));
}

/* ================= TESTES DE FILA ================= */
static void test_queue_basic() {
    printf(BOLD "Testes Básicos de Fila:\n" RESET);
    
    Queue *Q = create_queue();
    TEST_POINTER("Criação de fila", 0, Q);
    TEST_BOOL("Fila nova está vazia", 1, queue_is_empty(Q));
    
    // Enqueue e verificações
    enqueue(Q, 1);
    TEST_BOOL("Fila não vazia após enqueue", 0, queue_is_empty(Q));
    TEST_INT("Front após primeiro enqueue", 1, front(Q));
    
    enqueue(Q, 2);
    TEST_INT("Front mantém após segundo enqueue", 1, front(Q));
    
    enqueue(Q, 3);
    TEST_INT("Front mantém após terceiro enqueue", 1, front(Q));
    
    // Dequeue e verificações FIFO
    int dequeued = dequeue(Q);
    TEST_INT("Dequeue retorna primeiro elemento", 1, dequeued);
    TEST_INT("Front após dequeue", 2, front(Q));
    
    dequeue(Q);
    TEST_INT("Front após segundo dequeue", 3, front(Q));
    
    dequeue(Q);
    TEST_BOOL("Fila vazia após todos os dequeues", 1, queue_is_empty(Q));
}

static void test_queue_edge_cases() {
    printf(BOLD "\nTestes de Casos Extremos - Fila:\n" RESET);
    
    Queue *Q = create_queue();
    
    // Operações em fila vazia
    TEST_INT("Dequeue de fila vazia", -1, dequeue(Q));
    TEST_INT("Front de fila vazia", -1, front(Q));
    
    // Um elemento
    enqueue(Q, 42);
    TEST_INT("Front com um elemento", 42, front(Q));
    TEST_INT("Dequeue único elemento", 42, dequeue(Q));
    TEST_BOOL("Vazia após dequeue único", 1, queue_is_empty(Q));
    
    // Stress test - fila grande
    for(int i = 0; i < 1000; i++) {
        enqueue(Q, i);
    }
    TEST_INT("Front de fila grande", 0, front(Q));
    
    // Dequeue sequencial verificando ordem FIFO
    for(int i = 0; i < 3; i++) {
        int val = dequeue(Q);
        if (i == 0) TEST_INT("Dequeue ordem FIFO (0)", 0, val);
        else if (i == 1) TEST_INT("Dequeue ordem FIFO (1)", 1, val);
        else if (i == 2) TEST_INT("Dequeue ordem FIFO (2)", 2, val);
    }
}

static void test_queue_alternating() {
    printf(BOLD "\nTestes de Operações Alternadas - Fila:\n" RESET);
    
    Queue *Q = create_queue();
    
    // Padrão enqueue-dequeue alternado
    enqueue(Q, 10);
    TEST_INT("Front após enqueue", 10, front(Q));
    TEST_INT("Dequeue após enqueue", 10, dequeue(Q));
    TEST_BOOL("Vazia após ciclo", 1, queue_is_empty(Q));
    
    // Múltiplos ciclos - fila nova para evitar interferência
    Queue *Q2 = create_queue();
    enqueue(Q2, 11);
    enqueue(Q2, 12);
    TEST_INT("Front com dois elementos", 11, front(Q2));
    TEST_INT("Dequeue primeiro", 11, dequeue(Q2));
    TEST_INT("Front após dequeue", 12, front(Q2));
    
    enqueue(Q2, 13);
    TEST_INT("Front após enqueue no meio", 12, front(Q2));
}

/* ================= TESTES DE GRAFO ================= */

static void test_graph_creation() {
    printf(BOLD "Testes de Criação de Grafo:\n" RESET);
    
    // Grafos válidos
    Graph *G1 = create_graph(5, 0);  // Lista de adjacência
    TEST_POINTER("Criação grafo lista adjacência", 0, G1);
    
    Graph *G2 = create_graph(3, 1);  // Matriz de adjacência
    TEST_POINTER("Criação grafo matriz adjacência", 0, G2);
    
    // Casos extremos de criação
    Graph *G3 = create_graph(1, 0);  // Grafo com 1 vértice
    TEST_POINTER("Grafo com 1 vértice", 0, G3);
    
    Graph *G4 = create_graph(1000, 1);  // Grafo grande
    TEST_POINTER("Grafo grande (1000 vértices)", 0, G4);
    
    // Valores inválidos não testamos pois podem crashar
}

static void test_graph_edges_list() {
    printf(BOLD "\nTestes de Arestas - Lista de Adjacência:\n" RESET);
    
    Graph *G = create_graph(5, 0);
    
    // Adição de arestas válidas
    TEST_INT("Adicionar aresta 0-1", 1, add_edge(G, 0, 1));
    TEST_INT("Adicionar aresta 0-2", 1, add_edge(G, 0, 2));
    TEST_INT("Adicionar aresta 1-3", 1, add_edge(G, 1, 3));
    TEST_INT("Adicionar aresta 2-4", 1, add_edge(G, 2, 4));
    
    // Tentativa de adicionar aresta duplicada
    TEST_INT("Aresta duplicada 0-1", 0, add_edge(G, 0, 1));
    TEST_INT("Aresta duplicada 1-0", 0, add_edge(G, 1, 0));
    
    // Arestas inválidas
    TEST_INT("Aresta vértice negativo", 0, add_edge(G, -1, 2));
    TEST_INT("Aresta vértice muito grande", 0, add_edge(G, 0, 10));
    TEST_INT("Ambos vértices inválidos", 0, add_edge(G, -1, 10));
    
    // Remoção de arestas
    TEST_INT("Remover aresta existente 0-1", 1, remove_edge(G, 0, 1));
    TEST_INT("Remover aresta inexistente", 0, remove_edge(G, 0, 1));
    TEST_INT("Remover aresta nunca criada", 0, remove_edge(G, 3, 4));
    
    // Remoções inválidas
    TEST_INT("Remover vértice inválido", 0, remove_edge(G, -1, 2));
    TEST_INT("Remover vértice muito grande", 0, remove_edge(G, 0, 10));
}

static void test_graph_edges_matrix() {
    printf(BOLD "\nTestes de Arestas - Matriz de Adjacência:\n" RESET);
    
    Graph *G = create_graph(4, 1);
    
    // Adição de arestas válidas
    TEST_INT("Adicionar aresta 0-1", 1, add_edge(G, 0, 1));
    TEST_INT("Adicionar aresta 1-2", 1, add_edge(G, 1, 2));
    TEST_INT("Adicionar aresta 2-3", 1, add_edge(G, 2, 3));
    
    // Aresta duplicada
    TEST_INT("Aresta duplicada 0-1", 0, add_edge(G, 0, 1));
    
    // Casos extremos
    TEST_INT("Aresta para si mesmo", 1, add_edge(G, 0, 0)); // Self-loop
    TEST_INT("Self-loop duplicado", 0, add_edge(G, 0, 0));
    
    // Remoções
    TEST_INT("Remover aresta existente", 1, remove_edge(G, 1, 2));
    TEST_INT("Remover self-loop", 1, remove_edge(G, 0, 0));
    TEST_INT("Remover inexistente", 0, remove_edge(G, 1, 2));
}

static void test_graph_bfs_dfs() {
    printf(BOLD "\nTestes BFS e DFS:\n" RESET);
    
    // Grafo conectado pequeno
    Graph *G = create_graph(4, 0);
    add_edge(G, 0, 1);
    add_edge(G, 1, 2);
    add_edge(G, 2, 3);
    
    // BFS
    int *bfs_result = bfs(G, 0);
    TEST_POINTER("BFS retorna array válido", 0, bfs_result);
    if (bfs_result) {
        TEST_INT("BFS distância origem", 0, bfs_result[0]);
        TEST_INT("BFS distância 1", 1, bfs_result[1]);
        TEST_INT("BFS distância 2", 2, bfs_result[2]);
        TEST_INT("BFS distância 3", 3, bfs_result[3]);
        print_array("BFS de 0", bfs_result, 4);
        free(bfs_result);
    }
    
    // DFS
    int *dfs_result = dfs(G, 0);
    TEST_POINTER("DFS retorna array válido", 0, dfs_result);
    if (dfs_result) {
        TEST_INT("DFS origem", -1, dfs_result[0]);
        print_array("DFS de 0", dfs_result, 4);
        free(dfs_result);
    }
    
    // Casos inválidos
    int *bfs_invalid = bfs(G, 10);
    TEST_POINTER("BFS vértice inválido", 1, bfs_invalid);
    
    int *dfs_invalid = dfs(G, -1);
    TEST_POINTER("DFS vértice negativo", 1, dfs_invalid);
    
    int *bfs_null = bfs(NULL, 0);
    TEST_POINTER("BFS grafo NULL", 1, bfs_null);
}

static void test_graph_connectivity() {
    printf(BOLD "\nTestes de Conectividade:\n" RESET);
    
    // Grafo conectado
    Graph *G1 = create_graph(4, 1);
    add_edge(G1, 0, 1);
    add_edge(G1, 1, 2);
    add_edge(G1, 2, 3);
    TEST_BOOL("Grafo conectado", 1, is_connected(G1));
    
    // Grafo desconectado
    Graph *G2 = create_graph(5, 0);
    add_edge(G2, 0, 1);
    add_edge(G2, 3, 4);  // Componente separado
    TEST_BOOL("Grafo desconectado", 0, is_connected(G2));
    
    // Grafo vazio (sem arestas)
    Graph *G3 = create_graph(3, 1);
    TEST_BOOL("Grafo sem arestas", 0, is_connected(G3));
    
    // Grafo com um vértice
    Graph *G4 = create_graph(1, 0);
    TEST_BOOL("Grafo com 1 vértice", 1, is_connected(G4));
    
    // Grafo NULL
    TEST_BOOL("Grafo NULL", 0, is_connected(NULL));
}

static void test_graph_stress() {
    printf(BOLD "\nTestes de Stress - Grafo:\n" RESET);
    
    // Grafo grande com muitas arestas
    Graph *G = create_graph(100, 1);
    
    // Criar grafo completo (todos conectados a todos)
    int edges_added = 0;
    for(int i = 0; i < 100; i++) {
        for(int j = i + 1; j < 100; j++) {
            if(add_edge(G, i, j)) edges_added++;
        }
    }
    printf("    Arestas adicionadas: %d\n", edges_added);
    TEST_BOOL("Grafo completo conectado", 1, is_connected(G));
    
    // BFS e DFS em grafo grande
    int *bfs_large = bfs(G, 0);
    TEST_POINTER("BFS em grafo grande", 0, bfs_large);
    if (bfs_large) {
        TEST_INT("BFS distância máxima", 1, bfs_large[99]); // Grafo completo = dist 1
        free(bfs_large);
    }
}

/* ================= FUNÇÃO PRINCIPAL ================= */

void print_final_summary() {
    printf("\n");
    printf(BOLD CYAN "╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                       RESUMO FINAL DOS TESTES                   ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n" RESET);
    
    printf(BOLD "║  Total de Testes: " YELLOW "%3d" RESET BOLD "                                        ║\n", total_tests);
    printf("║  Testes Passou:   " GREEN "%3d" RESET BOLD " (" GREEN "%.1f%%" RESET BOLD ")                              ║\n", 
           passed_tests, total_tests > 0 ? (float)passed_tests/total_tests*100 : 0);
    printf("║  Testes Falharam: " RED "%3d" RESET BOLD " (" RED "%.1f%%" RESET BOLD ")                              ║\n", 
           failed_tests, total_tests > 0 ? (float)failed_tests/total_tests*100 : 0);
    
    printf(CYAN "╠══════════════════════════════════════════════════════════════╣\n");
    
    if (failed_tests == 0) {
        printf("║                    " GREEN "🎉 TODOS OS TESTES PASSARAM! 🎉" RESET "                   ║\n");
    } else if (failed_tests < passed_tests) {
        printf("║                  " YELLOW "⚠️  ALGUNS TESTES FALHARAM  ⚠️" RESET "                   ║\n");
    } else {
        printf("║                   " RED "❌ MUITOS TESTES FALHARAM ❌" RESET "                    ║\n");
    }
    
    printf(CYAN "╚══════════════════════════════════════════════════════════════╝" RESET "\n\n");
}

int main(void) {
    printf(BOLD MAGENTA "┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                 SISTEMA DE TESTES AVANÇADO                     │\n");
    printf("│                  Estruturas de Dados - ED1                     │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n" RESET);

    print_section_header("TESTES DE LISTA LIGADA");
    test_list_basic();
    test_list_edge_cases();
    test_list_null_pointers();

    print_section_header("TESTES DE PILHA");
    test_stack_basic();
    test_stack_edge_cases();
    test_stack_alternating();

    print_section_header("TESTES DE FILA");
    test_queue_basic();
    test_queue_edge_cases();
    test_queue_alternating();

    print_section_header("TESTES DE GRAFO");
    test_graph_creation();
    test_graph_edges_list();
    test_graph_edges_matrix();
    test_graph_bfs_dfs();
    test_graph_connectivity();
    test_graph_stress();

    print_final_summary();
    
    return (failed_tests == 0) ? 0 : 1;
}
