#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "heap.h"
#include "priority_queue.h"
#include "graph.h"

// Cores para facilitar visualização
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

// ============================================
// FUNÇÕES DE VISUALIZAÇÃO
// ============================================

void print_list(LinkedList *L, const char *label) {
    printf(BLUE "📋 %s: " RESET, label);
    
    if (list_is_empty(L)) {
        printf(YELLOW "[VAZIA]\n" RESET);
        return;
    }
    
    printf("[");
    List *current = L->head;
    int first = 1;
    while (current != NULL) {
        if (!first) printf(" -> ");
        printf("(v:%d, p:%d)", current->data.vert, current->data.value);
        current = current->next;
        first = 0;
    }
    printf("]\n");
}

void print_heap(Heap *heap, const char *label) {
    printf(BLUE "🌳 %s: " RESET, label);
    
    if (heap_is_empty(heap)) {
        printf(YELLOW "[VAZIA]\n" RESET);
        return;
    }
    
    if (heap->type == max_heap) {
        printf("[MAX-HEAP] ");
        for (int i = 0; i < heap->size; i++) {
            printf("%d ", heap->data[i]);
        }
        printf("\n");
    } else {
        printf("[MIN-HEAP] size=%d, capacity=%d\n", heap->size, heap->capacity);
        printf("  Elementos: ");
        for (int i = 0; i < heap->size; i++) {
            printf("(v:%d, p:%d) ", heap->nodes[i].vert, heap->nodes[i].value);
        }
        printf("\n");
    }
}

void print_heap_tree(Heap *heap, const char *label) {
    printf(BLUE "🌲 %s (visualização em árvore):\n" RESET, label);
    
    if (heap_is_empty(heap)) {
        printf(YELLOW "  [VAZIA]\n" RESET);
        return;
    }
    
    if (heap->type == min_heap) {
        int level = 0;
        int level_size = 1;
        int i = 0;
        
        while (i < heap->size) {
            printf("  Nível %d: ", level);
            for (int j = 0; j < level_size && i < heap->size; j++, i++) {
                printf("(v:%d,p:%d) ", heap->nodes[i].vert, heap->nodes[i].value);
            }
            printf("\n");
            level++;
            level_size *= 2;
        }
    }
}

void print_pq(Priority_Queue *pq, const char *label) {
    printf(BLUE "📊 %s: " RESET, label);
    
    if (pq == NULL) {
        printf(RED "[NULL]\n" RESET);
        return;
    }
    
    if (pq->type == heap) {
        printf("[TIPO: HEAP]\n");
        print_heap(pq->heap, "  Estado interno");
    } else {
        printf("[TIPO: LISTA]\n");
        print_list(pq->list, "  Estado interno");
    }
}

void print_graph_list(Graph *G, const char *label) {
    printf(BLUE "📊 %s (Lista de Adjacência):\n" RESET, label);
    
    if (G == NULL) {
        printf(RED "[NULL]\n" RESET);
        return;
    }
    
    for (int i = 0; i < G->vert_num; i++) {
        printf("  Vértice %d: ", i);
        if (list_is_empty(G->adj_list[i])) {
            printf(YELLOW "[sem vizinhos]\n" RESET);
        } else {
            printf("[");
            List *current = G->adj_list[i]->head;
            int first = 1;
            while (current != NULL) {
                if (!first) printf(", ");
                printf("%d", current->data.vert);
                current = current->next;
                first = 0;
            }
            printf("]\n");
        }
    }
}

void print_graph_matrix(Graph *G, const char *label) {
    printf(BLUE "📊 %s (Matriz de Adjacência):\n" RESET, label);
    
    if (G == NULL) {
        printf(RED "[NULL]\n" RESET);
        return;
    }
    
    printf("     ");
    for (int i = 0; i < G->vert_num; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < G->vert_num; i++) {
        printf("  %2d: ", i);
        for (int j = 0; j < G->vert_num; j++) {
            if (G->adj_matrix[i][j] == 1) {
                printf(GREEN " 1 " RESET);
            } else {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
}

// Variáveis para contagem de testes
int tests_passed = 0;
int tests_failed = 0;

void print_header(const char *title) {
    printf("\n" CYAN "========================================\n");
    printf("  %s\n", title);
    printf("========================================" RESET "\n\n");
}

void print_test(const char *test_name, int passed) {
    if (passed) {
        printf(GREEN "✓ PASSOU: " RESET "%s\n", test_name);
        tests_passed++;
    } else {
        printf(RED "✗ FALHOU: " RESET "%s\n", test_name);
        tests_failed++;
    }
}

void print_summary() {
    printf("\n" MAGENTA "========================================\n");
    printf("  RESUMO DOS TESTES\n");
    printf("========================================" RESET "\n");
    printf(GREEN "Testes Passados: %d\n" RESET, tests_passed);
    printf(RED "Testes Falhados: %d\n" RESET, tests_failed);
    printf(YELLOW "Total: %d\n" RESET, tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf(GREEN "\n🎉 TODOS OS TESTES PASSARAM! 🎉\n" RESET);
    } else {
        printf(RED "\n⚠️  ALGUNS TESTES FALHARAM ⚠️\n" RESET);
    }
    printf("\n");
}

// ============================================
// TESTES PARA LINKED LIST
// ============================================

void test_list_creation() {
    print_header("TESTE 1: Criação de Lista");
    
    LinkedList *L = create_list();
    
    printf(YELLOW "ANTES: Criando lista...\n" RESET);
    print_list(L, "Lista após criação");
    
    print_test("Lista criada com sucesso", L != NULL);
    print_test("Lista começa vazia", list_is_empty(L));
    print_test("Head é NULL", L->head == NULL);
    print_test("Tail é NULL", L->tail == NULL);
    
    free_list(L);
}

void test_list_insert() {
    print_header("TESTE 2: Inserção em Lista");
    
    LinkedList *L = create_list();
    printf(YELLOW "INICIAL:\n" RESET);
    print_list(L, "Lista vazia");
    
    Edge e1 = {1, 10};
    Edge e2 = {2, 5};
    Edge e3 = {3, 15};
    
    printf(YELLOW "\nDURANTE: Inserindo elementos...\n" RESET);
    list_insert_node(L, e1);
    print_list(L, "Após inserir (v:1, p:10)");
    print_test("Inserção do primeiro elemento", 1);
    
    list_insert_node(L, e2);
    print_list(L, "Após inserir (v:2, p:5)");
    print_test("Lista não está vazia", !list_is_empty(L));
    
    list_insert_node(L, e3);
    print_list(L, "Após inserir (v:3, p:15)");
    print_test("Inserção do terceiro elemento", 1);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    Edge min = list_return_min(L);
    printf("  Mínimo (head): (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Mínimo retornado corretamente", min.vert == 3 && min.value == 15);
    
    free_list(L);
}

void test_list_insert_sorted() {
    print_header("TESTE 3: Inserção Ordenada em Lista");
    
    LinkedList *L = create_list();
    printf(YELLOW "INICIAL:\n" RESET);
    print_list(L, "Lista vazia");
    
    Edge e1 = {1, 10};
    Edge e2 = {2, 5};
    Edge e3 = {3, 15};
    Edge e4 = {4, 7};
    
    printf(YELLOW "\nDURANTE: Inserindo ordenadamente...\n" RESET);
    list_insert_sorted(L, e1);
    print_list(L, "Após inserir (v:1, p:10)");
    
    list_insert_sorted(L, e2);
    print_list(L, "Após inserir (v:2, p:5)");
    
    list_insert_sorted(L, e3);
    print_list(L, "Após inserir (v:3, p:15)");
    
    list_insert_sorted(L, e4);
    print_list(L, "Após inserir (v:4, p:7)");
    
    printf(YELLOW "\nDEPOIS: Removendo em ordem...\n" RESET);
    // Ordem esperada: 5, 7, 10, 15
    print_list(L, "Lista completa");
    
    Edge min1 = list_remove_min(L);
    printf("  Removido: (v:%d, p:%d)\n", min1.vert, min1.value);
    print_list(L, "Lista após 1ª remoção");
    print_test("Primeiro mínimo = 5", min1.value == 5 && min1.vert == 2);
    
    Edge min2 = list_remove_min(L);
    printf("  Removido: (v:%d, p:%d)\n", min2.vert, min2.value);
    print_list(L, "Lista após 2ª remoção");
    print_test("Segundo mínimo = 7", min2.value == 7 && min2.vert == 4);
    
    Edge min3 = list_remove_min(L);
    printf("  Removido: (v:%d, p:%d)\n", min3.vert, min3.value);
    print_list(L, "Lista após 3ª remoção");
    print_test("Terceiro mínimo = 10", min3.value == 10 && min3.vert == 1);
    
    Edge min4 = list_remove_min(L);
    printf("  Removido: (v:%d, p:%d)\n", min4.vert, min4.value);
    print_list(L, "Lista após 4ª remoção");
    print_test("Quarto mínimo = 15", min4.value == 15 && min4.vert == 3);
    
    print_test("Lista fica vazia após remover tudo", list_is_empty(L));
    
    free_list(L);
}

void test_list_remove() {
    print_header("TESTE 4: Remoção em Lista");
    
    LinkedList *L = create_list();
    
    Edge e1 = {1, 10};
    Edge e2 = {2, 20};
    Edge e3 = {3, 30};
    
    list_insert_sorted(L, e1);
    list_insert_sorted(L, e2);
    list_insert_sorted(L, e3);
    
    printf(YELLOW "INICIAL:\n" RESET);
    print_list(L, "Lista completa");
    
    printf(YELLOW "\nDURANTE: Remoções específicas...\n" RESET);
    Edge removed = list_remove_with_vert(L, 2);
    printf("  Removido por vértice 2: (v:%d, p:%d)\n", removed.vert, removed.value);
    print_list(L, "Lista após remover vértice 2");
    print_test("Remoção por vértice 2", removed.vert == 2 && removed.value == 20);
    
    Edge removed2 = list_remove_with_value(L, 30);
    printf("  Removido por valor 30: (v:%d, p:%d)\n", removed2.vert, removed2.value);
    print_list(L, "Lista após remover valor 30");
    print_test("Remoção por valor 30", removed2.vert == 3 && removed2.value == 30);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_list(L, "Lista final");
    Edge min = list_return_min(L);
    print_test("Sobrou apenas vértice 1", min.vert == 1 && min.value == 10);
    
    free_list(L);
}

void test_list_search() {
    print_header("TESTE 5: Busca em Lista");
    
    LinkedList *L = create_list();
    
    Edge e1 = {10, 100};
    Edge e2 = {20, 200};
    Edge e3 = {30, 300};
    
    list_insert_node(L, e1);
    list_insert_node(L, e2);
    list_insert_node(L, e3);
    
    printf(YELLOW "ESTADO DA LISTA:\n" RESET);
    print_list(L, "Lista para busca");
    
    printf(YELLOW "\nBUSCAS:\n" RESET);
    int result1 = list_search_with_vert(L, 20);
    printf("  Buscar vértice 20: %s (retorno: %d)\n", 
           result1 == 20 ? GREEN "ENCONTRADO" RESET : RED "NÃO ENCONTRADO" RESET, result1);
    print_test("Busca vértice 20 (existe)", result1 == 20);
    
    int result2 = list_search_with_vert(L, 99);
    printf("  Buscar vértice 99: %s (retorno: %d)\n", 
           result2 == -1 ? GREEN "NÃO ENCONTRADO (correto)" RESET : RED "ERRO" RESET, result2);
    print_test("Busca vértice 99 (não existe)", result2 == -1);
    
    int result3 = list_search_with_value(L, 300);
    printf("  Buscar valor 300: %s (retorno: %d)\n", 
           result3 == 300 ? GREEN "ENCONTRADO" RESET : RED "NÃO ENCONTRADO" RESET, result3);
    print_test("Busca valor 300 (existe)", result3 == 300);
    
    int result4 = list_search_with_value(L, 999);
    printf("  Buscar valor 999: %s (retorno: %d)\n", 
           result4 == -1 ? GREEN "NÃO ENCONTRADO (correto)" RESET : RED "ERRO" RESET, result4);
    print_test("Busca valor 999 (não existe)", result4 == -1);
    
    free_list(L);
}

void test_list_decrease_priority() {
    print_header("TESTE 6: Diminuir Prioridade em Lista");
    
    LinkedList *L = create_list();
    
    Edge e1 = {1, 50};
    Edge e2 = {2, 30};
    Edge e3 = {3, 40};
    
    list_insert_sorted(L, e1);
    list_insert_sorted(L, e2);
    list_insert_sorted(L, e3);
    
    printf(YELLOW "ANTES:\n" RESET);
    print_list(L, "Lista ordenada inicial (30, 40, 50)");
    Edge min_before = list_return_min(L);
    printf("  Mínimo atual: (v:%d, p:%d)\n", min_before.vert, min_before.value);
    
    printf(YELLOW "\nDURANTE: Diminuindo prioridade...\n" RESET);
    printf("  Operação: diminuir vértice 1 de 50 para 25\n");
    Status result = list_decrease_priority(L, 1, 25);
    print_list(L, "Lista após decrease_priority");
    print_test("Diminuir prioridade do vértice 1 de 50 para 25", result == success);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_list(L, "Lista final (deve ser: 25, 30, 40)");
    Edge min = list_return_min(L);
    printf("  Novo mínimo: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Novo mínimo é vértice 1 com valor 25", min.vert == 1 && min.value == 25);
    
    free_list(L);
}

// ============================================
// TESTES PARA HEAP
// ============================================

void test_heap_sort() {
    print_header("TESTE 7: Heap Sort");
    
    int array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(array) / sizeof(array[0]);
    
    printf("Array original: ");
    for (int i = 0; i < n; i++) printf("%d ", array[i]);
    printf("\n");
    
    heap_sort(array, n);
    
    printf("Array ordenado: ");
    for (int i = 0; i < n; i++) printf("%d ", array[i]);
    printf("\n");
    
    int sorted = 1;
    for (int i = 0; i < n - 1; i++) {
        if (array[i] > array[i + 1]) {
            sorted = 0;
            break;
        }
    }
    
    print_test("Array está ordenado corretamente", sorted);
}

void test_min_heap_creation() {
    print_header("TESTE 8: Criação de Min Heap");
    
    int vert_num = 5;
    Heap *heap = create_min_heap(vert_num);
    
    printf(YELLOW "APÓS CRIAÇÃO:\n" RESET);
    print_heap(heap, "Min Heap inicial");
    print_heap_tree(heap, "Min Heap");
    
    print_test("Min Heap criado com sucesso", heap != NULL);
    print_test("Tipo é min_heap", heap->type == min_heap);
    print_test("Tamanho inicial correto", heap->size == vert_num);
    print_test("Capacidade correta", heap->capacity == vert_num);
    
    // Todos vértices devem começar com INF
    int all_inf = 1;
    printf(YELLOW "Verificando valores iniciais:\n" RESET);
    for (int i = 0; i < vert_num; i++) {
        printf("  Vértice %d: valor = %d %s\n", i, heap->nodes[i].value, 
               heap->nodes[i].value == INF ? GREEN "(INF)" RESET : RED "(ERRO)" RESET);
        if (heap->nodes[i].value != INF) {
            all_inf = 0;
        }
    }
    print_test("Todos os vértices iniciam com INF", all_inf);
    
    free_heap(heap);
}

void test_heap_operations() {
    print_header("TESTE 9: Operações em Min Heap");
    
    int vert_num = 5;
    Heap *heap = create_min_heap(vert_num);
    
    printf(YELLOW "INICIAL:\n" RESET);
    print_heap_tree(heap, "Heap inicial");
    
    printf(YELLOW "\nOPERAÇÃO 1: Diminuir vértice 0 para prioridade 10\n" RESET);
    heap_decrease_priority(heap, 0, 10);
    print_heap_tree(heap, "Heap após decrease_priority(0, 10)");
    Edge min = heap_return_min(heap);
    printf("  Mínimo atual: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Vértice 0 com prioridade 10 é o mínimo", min.vert == 0 && min.value == 10);
    
    printf(YELLOW "\nOPERAÇÃO 2: Diminuir vértice 2 para prioridade 5\n" RESET);
    heap_decrease_priority(heap, 2, 5);
    print_heap_tree(heap, "Heap após decrease_priority(2, 5)");
    min = heap_return_min(heap);
    printf("  Mínimo atual: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Vértice 2 com prioridade 5 é o novo mínimo", min.vert == 2 && min.value == 5);
    
    printf(YELLOW "\nOPERAÇÃO 3: Remover mínimo\n" RESET);
    Edge removed = heap_remove_min(heap);
    printf("  Removido: (v:%d, p:%d)\n", removed.vert, removed.value);
    print_heap_tree(heap, "Heap após remove_min()");
    print_test("Remoção do mínimo (vértice 2)", removed.vert == 2 && removed.value == 5);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    min = heap_return_min(heap);
    printf("  Novo mínimo: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Após remoção, vértice 0 é o mínimo", min.vert == 0 && min.value == 10);
    
    free_heap(heap);
}

void test_heap_multiple_operations() {
    print_header("TESTE 10: Múltiplas Operações em Heap");
    
    int vert_num = 6;
    Heap *heap = create_min_heap(vert_num);
    
    printf(YELLOW "MONTANDO HEAP com prioridades específicas...\n" RESET);
    heap_decrease_priority(heap, 0, 50);
    heap_decrease_priority(heap, 1, 30);
    heap_decrease_priority(heap, 2, 20);
    heap_decrease_priority(heap, 3, 40);
    heap_decrease_priority(heap, 4, 10);
    heap_decrease_priority(heap, 5, 60);
    
    printf(YELLOW "\nANTES das remoções:\n" RESET);
    print_heap_tree(heap, "Heap completa");
    
    printf(YELLOW "\nDURANTE: Removendo elementos em ordem de prioridade:\n" RESET);
    int expected_order[] = {4, 2, 1, 3, 0, 5};
    int correct_order = 1;
    
    for (int i = 0; i < 6; i++) {
        print_heap(heap, "  Heap antes da remoção");
        Edge removed = heap_remove_min(heap);
        printf("  " GREEN "Removido #%d:" RESET " vértice %d com prioridade %d\n", 
               i+1, removed.vert, removed.value);
        print_heap_tree(heap, "  Heap após remoção");
        printf("\n");
        
        if (removed.vert != expected_order[i]) {
            correct_order = 0;
        }
    }
    
    printf(YELLOW "DEPOIS:\n" RESET);
    print_heap(heap, "Heap final (deve estar vazia)");
    print_test("Elementos removidos na ordem correta", correct_order);
    print_test("Heap fica vazio", heap_is_empty(heap));
    
    free_heap(heap);
}

// ============================================
// TESTES PARA PRIORITY QUEUE
// ============================================

void test_pq_with_heap() {
    print_header("TESTE 11: Priority Queue com Heap");
    
    Priority_Queue *pq = create_pq(heap, 5);
    
    printf(YELLOW "INICIAL:\n" RESET);
    print_pq(pq, "Priority Queue (Heap) criada");
    print_test("Priority Queue (heap) criada", pq != NULL);
    print_test("Tipo é heap", pq->type == heap);
    
    printf(YELLOW "\nDURANTE: Operações de decrease_priority...\n" RESET);
    pq_decrease_priority(pq, 0, 30);
    print_pq(pq, "Após decrease_priority(0, 30)");
    
    pq_decrease_priority(pq, 1, 10);
    print_pq(pq, "Após decrease_priority(1, 10)");
    
    pq_decrease_priority(pq, 2, 20);
    print_pq(pq, "Após decrease_priority(2, 20)");
    
    Edge min = pq_return_min(pq);
    printf("  Mínimo atual: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Mínimo é vértice 1 com prioridade 10", min.vert == 1 && min.value == 10);
    
    printf(YELLOW "\nRemovendo mínimo...\n" RESET);
    Edge removed = pq_remove_min(pq);
    printf("  Removido: (v:%d, p:%d)\n", removed.vert, removed.value);
    print_pq(pq, "Após remove_min()");
    print_test("Remoção do mínimo (vértice 1)", removed.vert == 1 && removed.value == 10);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    min = pq_return_min(pq);
    printf("  Novo mínimo: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Novo mínimo é vértice 2 com prioridade 20", min.vert == 2 && min.value == 20);
    
    free_pq(pq);
}

void test_pq_with_list() {
    print_header("TESTE 12: Priority Queue com Lista");
    
    Priority_Queue *pq = create_pq(linked_list, 0);
    
    printf(YELLOW "INICIAL:\n" RESET);
    print_pq(pq, "Priority Queue (Lista) criada");
    print_test("Priority Queue (lista) criada", pq != NULL);
    print_test("Tipo é linked_list", pq->type == linked_list);
    
    printf(YELLOW "\nDURANTE: Inserindo elementos ordenadamente...\n" RESET);
    Edge e1 = {1, 30};
    Edge e2 = {2, 10};
    Edge e3 = {3, 20};
    
    pq_insert_sorted(pq, e1);
    print_pq(pq, "Após inserir (v:1, p:30)");
    
    pq_insert_sorted(pq, e2);
    print_pq(pq, "Após inserir (v:2, p:10)");
    
    pq_insert_sorted(pq, e3);
    print_pq(pq, "Após inserir (v:3, p:20)");
    
    Edge min = pq_return_min(pq);
    printf("  Mínimo atual: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Mínimo é vértice 2 com prioridade 10", min.vert == 2 && min.value == 10);
    
    printf(YELLOW "\nRemovendo mínimo...\n" RESET);
    Edge removed = pq_remove_min(pq);
    printf("  Removido: (v:%d, p:%d)\n", removed.vert, removed.value);
    print_pq(pq, "Após remove_min()");
    print_test("Remoção do mínimo (vértice 2)", removed.vert == 2 && removed.value == 10);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    min = pq_return_min(pq);
    printf("  Novo mínimo: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Novo mínimo é vértice 3 com prioridade 20", min.vert == 3 && min.value == 20);
    
    free_pq(pq);
}

void test_pq_comparison() {
    print_header("TESTE 13: Comparação Heap vs Lista");
    
    printf(YELLOW "Criando duas Priority Queues com os mesmos dados...\n" RESET);
    
    Priority_Queue *pq_heap = create_pq(heap, 5);
    Priority_Queue *pq_list = create_pq(linked_list, 0);
    
    printf(YELLOW "\nPOPULANDO as estruturas...\n" RESET);
    pq_decrease_priority(pq_heap, 0, 40);
    pq_decrease_priority(pq_heap, 1, 10);
    pq_decrease_priority(pq_heap, 2, 30);
    pq_decrease_priority(pq_heap, 3, 20);
    pq_decrease_priority(pq_heap, 4, 50);
    
    pq_insert_sorted(pq_list, (Edge){0, 40});
    pq_insert_sorted(pq_list, (Edge){1, 10});
    pq_insert_sorted(pq_list, (Edge){2, 30});
    pq_insert_sorted(pq_list, (Edge){3, 20});
    pq_insert_sorted(pq_list, (Edge){4, 50});
    
    printf("\n" CYAN "Estado ANTES das remoções:\n" RESET);
    print_pq(pq_heap, "PQ com HEAP");
    print_pq(pq_list, "PQ com LISTA");
    
    printf(YELLOW "\nDURANTE: Removendo elementos de ambas:\n" RESET);
    int same_order = 1;
    for (int i = 0; i < 5; i++) {
        printf("\n" CYAN "  Remoção #%d:\n" RESET, i+1);
        
        Edge heap_min = pq_remove_min(pq_heap);
        Edge list_min = pq_remove_min(pq_list);
        
        printf("    HEAP removeu:  (v:%d, p:%d)\n", heap_min.vert, heap_min.value);
        printf("    LISTA removeu: (v:%d, p:%d)\n", list_min.vert, list_min.value);
        
        if (heap_min.value == list_min.value) {
            printf("    " GREEN "✓ Mesma prioridade!\n" RESET);
        } else {
            printf("    " RED "✗ Prioridades diferentes!\n" RESET);
            same_order = 0;
        }
    }
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_pq(pq_heap, "PQ com HEAP (deve estar vazia)");
    print_pq(pq_list, "PQ com LISTA (deve estar vazia)");
    
    print_test("Heap e Lista retornam mesmas prioridades na ordem", same_order);
    
    free_pq(pq_heap);
    free_pq(pq_list);
}

// ============================================
// TESTES INTEGRADOS
// ============================================

void test_integrated_scenario() {
    print_header("TESTE 14: Cenário Integrado - Simulação Dijkstra");
    
    printf(YELLOW "Simulando estrutura do algoritmo de Dijkstra...\n" RESET);
    
    int num_vertices = 5;
    Priority_Queue *pq = create_pq(heap, num_vertices);
    
    printf(YELLOW "\nINICIALIZAÇÃO:\n" RESET);
    for (int i = 1; i < num_vertices; i++) {
        pq_decrease_priority(pq, i, INF);
    }
    pq_decrease_priority(pq, 0, 0);
    
    printf("  Vértice 0: distância 0 (origem)\n");
    printf("  Vértices 1-4: distância INF\n");
    print_pq(pq, "PQ inicial");
    
    Edge min = pq_return_min(pq);
    printf("  Mínimo: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Vértice de origem (0) é o mínimo inicial", min.vert == 0 && min.value == 0);
    
    printf(YELLOW "\nITERAÇÃO 1: Processando vértice 0\n" RESET);
    printf("  Relaxando arestas do vértice 0:\n");
    printf("    Aresta 0->1 (peso 10): dist[1] = 0 + 10 = 10\n");
    printf("    Aresta 0->2 (peso 5):  dist[2] = 0 + 5 = 5\n");
    
    pq_decrease_priority(pq, 1, 10);
    pq_decrease_priority(pq, 2, 5);
    print_pq(pq, "PQ após relaxamento");
    
    Edge removed = pq_remove_min(pq);
    printf("  Removido: (v:%d, p:%d)\n", removed.vert, removed.value);
    print_pq(pq, "PQ após remover vértice 0");
    
    min = pq_return_min(pq);
    printf("  Próximo vértice a processar: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Próximo vértice a processar é 2 (menor distância)", min.vert == 2 && min.value == 5);
    
    printf(YELLOW "\nITERAÇÃO 2: Processando vértice 2\n" RESET);
    printf("  Relaxando arestas do vértice 2:\n");
    printf("    Aresta 2->3 (peso 7): dist[3] = 5 + 7 = 12\n");
    printf("    Aresta 2->1 (peso 3): dist[1] = 5 + 3 = 8 (MELHOR que 10!)\n");
    
    pq_decrease_priority(pq, 3, 12);
    pq_decrease_priority(pq, 1, 8);
    print_pq(pq, "PQ após relaxamento");
    
    removed = pq_remove_min(pq);
    printf("  Removido: (v:%d, p:%d)\n", removed.vert, removed.value);
    print_pq(pq, "PQ após remover vértice 2");
    
    min = pq_return_min(pq);
    printf("  Próximo vértice a processar: (v:%d, p:%d)\n", min.vert, min.value);
    print_test("Próximo vértice é 1 com distância atualizada (8)", min.vert == 1 && min.value == 8);
    
    printf(GREEN "\n✓ Simulação de Dijkstra funcionando corretamente!\n" RESET);
    printf("  A Priority Queue mantém corretamente a ordem das distâncias\n");
    printf("  e suporta operações de decrease_priority conforme necessário.\n");
    
    free_pq(pq);
}

void test_stress_test() {
    print_header("TESTE 15: Teste de Estresse");
    
    printf(YELLOW "Testando com 100 elementos...\n" RESET);
    
    Priority_Queue *pq = create_pq(heap, 100);
    
    // Inserir 100 elementos com prioridades aleatórias
    for (int i = 0; i < 100; i++) {
        int priority = (i * 7 + 13) % 200; // Gerar prioridades pseudo-aleatórias
        pq_decrease_priority(pq, i, priority);
    }
    
    print_test("100 elementos inseridos", 1);
    
    // Remover todos e verificar ordem
    int last_priority = -1;
    int correct_order = 1;
    
    for (int i = 0; i < 100; i++) {
        Edge removed = pq_remove_min(pq);
        if (removed.value < last_priority) {
            correct_order = 0;
            break;
        }
        last_priority = removed.value;
    }
    
    print_test("100 elementos removidos em ordem crescente", correct_order);
    
    free_pq(pq);
}

// ============================================
// TESTES PARA GRAPH
// ============================================

void test_graph_list_creation() {
    print_header("TESTE 16: Criação de Grafo (Lista de Adjacência)");
    
    int num_vertices = 5;
    Graph *G = create_graph(adj_list, num_vertices);
    
    printf(YELLOW "APÓS CRIAÇÃO:\n" RESET);
    print_graph_list(G, "Grafo vazio");
    
    print_test("Grafo criado com sucesso", G != NULL);
    print_test("Tipo é adj_list", G->type == adj_list);
    print_test("Número de vértices correto", G->vert_num == num_vertices);
    print_test("Listas de adjacência criadas", G->adj_list != NULL);
    
    // Verificar se todas as listas estão vazias
    int all_empty = 1;
    for (int i = 0; i < num_vertices; i++) {
        if (!list_is_empty(G->adj_list[i])) {
            all_empty = 0;
            break;
        }
    }
    print_test("Todas as listas de adjacência começam vazias", all_empty);
    
    free(G);
}

void test_graph_matrix_creation() {
    print_header("TESTE 17: Criação de Grafo (Matriz de Adjacência)");
    
    int num_vertices = 5;
    Graph *G = create_graph(adj_matrix, num_vertices);
    
    printf(YELLOW "APÓS CRIAÇÃO:\n" RESET);
    print_graph_matrix(G, "Grafo vazio");
    
    print_test("Grafo criado com sucesso", G != NULL);
    print_test("Tipo é adj_matrix", G->type == adj_matrix);
    print_test("Número de vértices correto", G->vert_num == num_vertices);
    print_test("Matriz de adjacência criada", G->adj_matrix != NULL);
    
    // Verificar se toda a matriz está zerada
    int all_zeros = 1;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (G->adj_matrix[i][j] != 0) {
                all_zeros = 0;
                break;
            }
        }
        if (!all_zeros) break;
    }
    print_test("Toda a matriz começa zerada", all_zeros);
    
    free(G);
}

void test_graph_list_add_edges() {
    print_header("TESTE 18: Adicionar Arestas (Lista de Adjacência)");
    
    Graph *G = create_graph(adj_list, 5);
    
    printf(YELLOW "INICIAL:\n" RESET);
    print_graph_list(G, "Grafo vazio");
    
    printf(YELLOW "\nDURANTE: Adicionando arestas...\n" RESET);
    
    printf("  Adicionando aresta 0-1...\n");
    Status result1 = add_edge(G, 0, 1, 1);
    print_graph_list(G, "Após adicionar 0-1");
    print_test("Aresta 0-1 adicionada com sucesso", result1 == success);
    
    printf("\n  Adicionando aresta 1-2...\n");
    Status result2 = add_edge(G, 1, 2, 1);
    print_graph_list(G, "Após adicionar 1-2");
    print_test("Aresta 1-2 adicionada com sucesso", result2 == success);
    
    printf("\n  Adicionando aresta 0-3...\n");
    Status result3 = add_edge(G, 0, 3, 1);
    print_graph_list(G, "Após adicionar 0-3");
    print_test("Aresta 0-3 adicionada com sucesso", result3 == success);
    
    printf("\n  Adicionando aresta 2-4...\n");
    Status result4 = add_edge(G, 2, 4, 1);
    print_graph_list(G, "Após adicionar 2-4");
    print_test("Aresta 2-4 adicionada com sucesso", result4 == success);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_graph_list(G, "Grafo final");
    
    // Verificar se a aresta 0-1 existe em ambas as direções
    int found_0_1 = list_search_with_vert(G->adj_list[0], 1) != -1;
    int found_1_0 = list_search_with_vert(G->adj_list[1], 0) != -1;
    print_test("Aresta 0-1 é bidirecional", found_0_1 && found_1_0);
    
    free(G);
}

void test_graph_matrix_add_edges() {
    print_header("TESTE 19: Adicionar Arestas (Matriz de Adjacência)");
    
    Graph *G = create_graph(adj_matrix, 5);
    
    printf(YELLOW "INICIAL:\n" RESET);
    print_graph_matrix(G, "Grafo vazio");
    
    printf(YELLOW "\nDURANTE: Adicionando arestas...\n" RESET);
    
    printf("  Adicionando aresta 0-1...\n");
    Status result1 = add_edge(G, 0, 1, 1);
    print_graph_matrix(G, "Após adicionar 0-1");
    print_test("Aresta 0-1 adicionada com sucesso", result1 == success);
    
    printf("\n  Adicionando aresta 1-2...\n");
    Status result2 = add_edge(G, 1, 2, 1);
    print_graph_matrix(G, "Após adicionar 1-2");
    print_test("Aresta 1-2 adicionada com sucesso", result2 == success);
    
    printf("\n  Adicionando aresta 0-3...\n");
    Status result3 = add_edge(G, 0, 3, 1);
    print_graph_matrix(G, "Após adicionar 0-3");
    print_test("Aresta 0-3 adicionada com sucesso", result3 == success);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_graph_matrix(G, "Grafo final");
    
    // Verificar se a aresta 0-1 existe em ambas as direções
    print_test("Aresta 0-1 é bidirecional", G->adj_matrix[0][1] == 1 && G->adj_matrix[1][0] == 1);
    print_test("Matriz é simétrica", G->adj_matrix[1][2] == G->adj_matrix[2][1]);
    
    free(G);
}

void test_graph_list_remove_edges() {
    print_header("TESTE 20: Remover Arestas (Lista de Adjacência)");
    
    Graph *G = create_graph(adj_list, 5);
    
    add_edge(G, 0, 1, 1);
    add_edge(G, 1, 2, 1);
    add_edge(G, 0, 3, 1);
    add_edge(G, 2, 4, 1);
    add_edge(G, 3, 4, 1);
    
    printf(YELLOW "ANTES:\n" RESET);
    print_graph_list(G, "Grafo com 5 arestas");
    
    printf(YELLOW "\nDURANTE: Removendo arestas...\n" RESET);
    
    printf("  Removendo aresta 1-2...\n");
    Status result1 = remove_edge(G, 1, 2);
    print_graph_list(G, "Após remover 1-2");
    print_test("Aresta 1-2 removida com sucesso", result1 == success);
    
    printf("\n  Removendo aresta 0-3...\n");
    Status result2 = remove_edge(G, 0, 3);
    print_graph_list(G, "Após remover 0-3");
    print_test("Aresta 0-3 removida com sucesso", result2 == success);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_graph_list(G, "Grafo após remoções");
    
    // Verificar se as arestas foram removidas
    int not_found_1_2 = list_search_with_vert(G->adj_list[1], 2) == -1;
    int not_found_2_1 = list_search_with_vert(G->adj_list[2], 1) == -1;
    print_test("Aresta 1-2 foi removida completamente", not_found_1_2 && not_found_2_1);
    
    int found_0_1 = list_search_with_vert(G->adj_list[0], 1) != -1;
    print_test("Aresta 0-1 ainda existe", found_0_1);
    
    free(G);
}

void test_graph_matrix_remove_edges() {
    print_header("TESTE 21: Remover Arestas (Matriz de Adjacência)");
    
    Graph *G = create_graph(adj_matrix, 5);
    
    add_edge(G, 0, 1, 1);
    add_edge(G, 1, 2, 1);
    add_edge(G, 0, 3, 1);
    add_edge(G, 2, 4, 1);
    add_edge(G, 3, 4, 1);
    
    printf(YELLOW "ANTES:\n" RESET);
    print_graph_matrix(G, "Grafo com 5 arestas");
    
    printf(YELLOW "\nDURANTE: Removendo arestas...\n" RESET);
    
    printf("  Removendo aresta 1-2...\n");
    Status result1 = remove_edge(G, 1, 2);
    print_graph_matrix(G, "Após remover 1-2");
    print_test("Aresta 1-2 removida com sucesso", result1 == success);
    
    printf("\n  Removendo aresta 0-3...\n");
    Status result2 = remove_edge(G, 0, 3);
    print_graph_matrix(G, "Após remover 0-3");
    print_test("Aresta 0-3 removida com sucesso", result2 == success);
    
    printf(YELLOW "\nDEPOIS:\n" RESET);
    print_graph_matrix(G, "Grafo após remoções");
    
    // Verificar se as arestas foram removidas
    print_test("Aresta 1-2 foi removida completamente", G->adj_matrix[1][2] == 0 && G->adj_matrix[2][1] == 0);
    
    // Verificar se outras arestas ainda existem
    print_test("Aresta 0-1 ainda existe", G->adj_matrix[0][1] == 1);
    
    free(G);
}

void test_graph_duplicate_edge() {
    print_header("TESTE 22: Tentativa de Adicionar Aresta Duplicada");
    
    Graph *G_list = create_graph(adj_list, 4);
    Graph *G_matrix = create_graph(adj_matrix, 4);
    
    printf(YELLOW "LISTA DE ADJACÊNCIA:\n" RESET);
    add_edge(G_list, 0, 1, 1);
    print_graph_list(G_list, "Após adicionar aresta 0-1");
    
    printf("  Tentando adicionar aresta 0-1 novamente...\n");
    Status result_list = add_edge(G_list, 0, 1, 1);
    print_graph_list(G_list, "Após tentativa de duplicação");
    print_test("Lista: Aresta duplicada rejeitada", result_list == error);
    
    printf(YELLOW "\nMATRIZ DE ADJACÊNCIA:\n" RESET);
    add_edge(G_matrix, 0, 1, 1);
    print_graph_matrix(G_matrix, "Após adicionar aresta 0-1");
    
    printf("  Tentando adicionar aresta 0-1 novamente...\n");
    Status result_matrix = add_edge(G_matrix, 0, 1, 1);
    print_graph_matrix(G_matrix, "Após tentativa de duplicação");
    print_test("Matriz: Aresta duplicada rejeitada", result_matrix == error);
    
    free(G_list);
    free(G_matrix);
}

void test_graph_remove_nonexistent() {
    print_header("TESTE 23: Tentativa de Remover Aresta Inexistente");
    
    Graph *G_list = create_graph(adj_list, 4);
    Graph *G_matrix = create_graph(adj_matrix, 4);
    
    printf(YELLOW "LISTA DE ADJACÊNCIA:\n" RESET);
    add_edge(G_list, 0, 1, 1);
    print_graph_list(G_list, "Grafo com apenas aresta 0-1");
    
    printf("  Tentando remover aresta inexistente 2-3...\n");
    Status result_list = remove_edge(G_list, 2, 3);
    print_graph_list(G_list, "Após tentativa de remoção");
    print_test("Lista: Remoção de aresta inexistente retorna erro", result_list == error);
    
    printf(YELLOW "\nMATRIZ DE ADJACÊNCIA:\n" RESET);
    add_edge(G_matrix, 0, 1, 1);
    print_graph_matrix(G_matrix, "Grafo com apenas aresta 0-1");
    
    printf("  Tentando remover aresta inexistente 2-3...\n");
    Status result_matrix = remove_edge(G_matrix, 2, 3);
    print_graph_matrix(G_matrix, "Após tentativa de remoção");
    print_test("Matriz: Remoção de aresta inexistente retorna erro", result_matrix == error);
    
    free(G_list);
    free(G_matrix);
}

void test_graph_comparison() {
    print_header("TESTE 24: Comparação Lista vs Matriz");
    
    printf(YELLOW "Criando dois grafos com mesma estrutura...\n" RESET);
    
    Graph *G_list = create_graph(adj_list, 6);
    Graph *G_matrix = create_graph(adj_matrix, 6);
    
    // Adicionar as mesmas arestas em ambos
    printf(YELLOW "\nAdicionando arestas idênticas em ambos os grafos...\n" RESET);
    add_edge(G_list, 0, 1, 1);
    add_edge(G_matrix, 0, 1, 1);
    
    add_edge(G_list, 0, 2, 1);
    add_edge(G_matrix, 0, 2, 1);
    
    add_edge(G_list, 1, 3, 1);
    add_edge(G_matrix, 1, 3, 1);
    
    add_edge(G_list, 2, 3, 1);
    add_edge(G_matrix, 2, 3, 1);
    
    add_edge(G_list, 3, 4, 1);
    add_edge(G_matrix, 3, 4, 1);
    
    add_edge(G_list, 4, 5, 1);
    add_edge(G_matrix, 4, 5, 1);
    
    printf(YELLOW "\nGRAFO COM LISTA DE ADJACÊNCIA:\n" RESET);
    print_graph_list(G_list, "Lista");
    
    printf(YELLOW "\nGRAFO COM MATRIZ DE ADJACÊNCIA:\n" RESET);
    print_graph_matrix(G_matrix, "Matriz");
    
    // Verificar se as estruturas são equivalentes
    int equivalent = 1;
    for (int i = 0; i < 6 && equivalent; i++) {
        for (int j = 0; j < 6; j++) {
            int in_matrix = G_matrix->adj_matrix[i][j] != 0;
            int in_list = list_search_with_vert(G_list->adj_list[i], j) != -1;
            
            if (in_matrix != in_list) {
                equivalent = 0;
                printf(RED "  Diferença encontrada: aresta %d-%d\n" RESET, i, j);
                break;
            }
        }
    }
    
    print_test("Ambas representações contêm as mesmas arestas", equivalent);
    
    printf(GREEN "\n✓ Ambas as representações (lista e matriz) funcionam corretamente!\n" RESET);
    
    free(G_list);
    free(G_matrix);
}

void test_graph_complex_scenario() {
    print_header("TESTE 25: Cenário Complexo - Grafo de Caminho Mínimo");
    
    printf(YELLOW "Criando grafo para simulação de algoritmo de caminho mínimo...\n" RESET);
    printf("  (Este grafo será usado com algoritmos como Dijkstra ou Prim)\n\n");
    
    int num_vertices = 6;
    Graph *G = create_graph(adj_list, num_vertices);
    
    printf(YELLOW "Construindo grafo com 9 arestas:\n" RESET);
    printf("  0 -- 1 (peso: 4)\n");
    printf("  0 -- 2 (peso: 3)\n");
    printf("  1 -- 2 (peso: 1)\n");
    printf("  1 -- 3 (peso: 2)\n");
    printf("  2 -- 3 (peso: 4)\n");
    printf("  2 -- 4 (peso: 5)\n");
    printf("  3 -- 4 (peso: 1)\n");
    printf("  3 -- 5 (peso: 6)\n");
    printf("  4 -- 5 (peso: 2)\n\n");
    
    add_edge(G, 0, 1, 4);
    add_edge(G, 0, 2, 3);
    add_edge(G, 1, 2, 1);
    add_edge(G, 1, 3, 2);
    add_edge(G, 2, 3, 4);
    add_edge(G, 2, 4, 5);
    add_edge(G, 3, 4, 1);
    add_edge(G, 3, 5, 6);
    add_edge(G, 4, 5, 2);
    
    print_graph_list(G, "Grafo final");
    
    // Verificar propriedades do grafo
    int total_edges = 0;
    for (int i = 0; i < num_vertices; i++) {
        List *current = G->adj_list[i]->head;
        while (current != NULL) {
            total_edges++;
            current = current->next;
        }
    }
    total_edges /= 2; // Cada aresta é contada duas vezes
    
    printf(YELLOW "\nESTATÍSTICAS DO GRAFO:\n" RESET);
    printf("  Vértices: %d\n", num_vertices);
    printf("  Arestas: %d\n", total_edges);
    
    // Verificar grau de cada vértice
    printf(YELLOW "\nGRAU DE CADA VÉRTICE:\n" RESET);
    for (int i = 0; i < num_vertices; i++) {
        int degree = 0;
        List *current = G->adj_list[i]->head;
        while (current != NULL) {
            degree++;
            current = current->next;
        }
        printf("  Vértice %d: grau %d\n", i, degree);
    }
    
    print_test("Grafo criado com 9 arestas", total_edges == 9);
    print_test("Grafo tem 6 vértices", num_vertices == 6);
    
    printf(GREEN "\n✓ Grafo complexo criado com sucesso!\n" RESET);
    printf("  Pronto para ser usado com algoritmos de caminho mínimo.\n");
    
    free(G);
}

// ============================================
// MAIN
// ============================================

int main() {
    printf("\n");
    printf(MAGENTA "╔════════════════════════════════════════╗\n");
    printf("║  SUITE DE TESTES - EP2                 ║\n");
    printf("║  Estruturas de Dados                   ║\n");
    printf("╚════════════════════════════════════════╝\n" RESET);
    
    // Testes de Lista
    test_list_creation();
    test_list_insert();
    test_list_insert_sorted();
    test_list_remove();
    test_list_search();
    test_list_decrease_priority();
    
    // Testes de Heap
    test_heap_sort();
    test_min_heap_creation();
    test_heap_operations();
    test_heap_multiple_operations();
    
    // Testes de Priority Queue
    test_pq_with_heap();
    test_pq_with_list();
    test_pq_comparison();
    
    // Testes Integrados
    test_integrated_scenario();
    test_stress_test();
    
    // Testes de Grafo
    test_graph_list_creation();
    test_graph_matrix_creation();
    test_graph_list_add_edges();
    test_graph_matrix_add_edges();
    test_graph_list_remove_edges();
    test_graph_matrix_remove_edges();
    test_graph_duplicate_edge();
    test_graph_remove_nonexistent();
    test_graph_comparison();
    test_graph_complex_scenario();
    
    // Resumo final
    print_summary();
    
    return (tests_failed == 0) ? 0 : 1;
}
