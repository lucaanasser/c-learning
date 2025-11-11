#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graph.h"

double get_time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000.0;
}

// Função para gerar um grafo com densidade controlada (mais eficiente)
void generate_graph_edges_efficient(Graph *G, int vertices, int target_edges) {
    // notas: geração por embaralhamento evita repetição sem checagens extras
    
    // Cria lista de todas as possíveis arestas
    int max_possible = (vertices * (vertices - 1)) / 2;
    if (target_edges > max_possible) target_edges = max_possible;
    
    int **possible_edges = malloc(max_possible * sizeof(int*));
    for (int i = 0; i < max_possible; i++) {
        possible_edges[i] = malloc(2 * sizeof(int));
    }
    
    int edge_count = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            possible_edges[edge_count][0] = i;
            possible_edges[edge_count][1] = j;
            edge_count++;
        }
    }
    
    // Embaralha a lista de arestas
    // embaralhamento usando rand() (seed definido em main)
    for (int i = 0; i < max_possible; i++) {
        int j = rand() % max_possible;
        int temp[2] = {possible_edges[i][0], possible_edges[i][1]};
        possible_edges[i][0] = possible_edges[j][0];
        possible_edges[i][1] = possible_edges[j][1];
        possible_edges[j][0] = temp[0];
        possible_edges[j][1] = temp[1];
    }
    
    // Adiciona as primeiras target_edges arestas
    for (int i = 0; i < target_edges; i++) {
        add_edge(G, possible_edges[i][0], possible_edges[i][1]);
    }
    
    // Libera memória
    for (int i = 0; i < max_possible; i++) {
        free(possible_edges[i]);
    }
    free(possible_edges);
}

// Função auxiliar para calcular média e desvio padrão
static void compute_stats(double *vals, int n, double *avg, double *std) {
    double s = 0.0, sq = 0.0;
    for (int i = 0; i < n; i++) { s += vals[i]; sq += vals[i] * vals[i]; }
    *avg = s / n;
    double var = (sq / n) - (*avg) * (*avg);
    *std = (var > 0) ? sqrt(var) : 0.0;
}

// Execução dos testes de desempenho conforme enunciado
void run_performance_tests() {
    const int small_vertices = 10;
    const int medium_vertices = 100;
    const int large_vertices = 500;
    const int num_experiments = 15;

    double densities[] = {0.05, 0.50, 0.90};
    const char* density_cat[] = {"ESPARSA", "MEDIA", "DENSA"};
    int vertices_configs[] = {small_vertices, medium_vertices, large_vertices};
    const char* size_names[] = {"PEQUENO", "MÉDIO", "GRANDE"};

    printf("RESULTADOS (microssegundos: média ± desvio)\n");
    printf("Legenda: Cat densidade (ESPARSA≈5%%, MEDIA≈50%%, DENSA≈90%% do máximo V(V-1)/2).\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-7s %-7s %7s %9s %-8s %18s %18s %18s\n",
           "Tam", "Cat", "V", "E", "Tipo", "Construção", "BFS", "DFS");
    printf("%-7s %-7s %7s %9s %-8s %18s %18s %18s\n",
           "-------", "-------", "-------", "---------", "--------", "------------------", "------------------", "------------------");

    for (int size_idx = 0; size_idx < 3; size_idx++) {
        int vertices = vertices_configs[size_idx];
        long max_edges = (long)vertices * (vertices - 1) / 2;

        for (int dens_idx = 0; dens_idx < 3; dens_idx++) {
            double d = densities[dens_idx];
            int expected_edges = (int)(max_edges * d);

            for (int graph_type = 0; graph_type <= 1; graph_type++) {
                double construction_times[num_experiments];
                double bfs_times[num_experiments];
                double dfs_times[num_experiments];

                for (int exp = 0; exp < num_experiments; exp++) {
                    struct timespec start, end;

                    clock_gettime(CLOCK_MONOTONIC, &start);
                    Graph *G = create_graph(vertices, graph_type);
                    generate_graph_edges_efficient(G, vertices, expected_edges);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    construction_times[exp] = get_time_diff(start, end);

                    clock_gettime(CLOCK_MONOTONIC, &start);
                    int* bfs_result = bfs(G, 0);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    bfs_times[exp] = get_time_diff(start, end);
                    free(bfs_result);

                    clock_gettime(CLOCK_MONOTONIC, &start);
                    int* dfs_result = dfs(G, 0);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    dfs_times[exp] = get_time_diff(start, end);
                    free(dfs_result);

                    destroy_graph(G);
                }

                double avg_c, std_c, avg_b, std_b, avg_d, std_d;
                compute_stats(construction_times, num_experiments, &avg_c, &std_c);
                compute_stats(bfs_times, num_experiments, &avg_b, &std_b);
                compute_stats(dfs_times, num_experiments, &avg_d, &std_d);

                printf("%-7s %-7s %7d %9d %-8s %9.2f ± %7.2f %9.2f ± %7.2f %9.2f ± %7.2f\n",
                       size_names[size_idx],
                       density_cat[dens_idx],
                       vertices,
                       expected_edges,
                       (graph_type == 0 ? "Lista" : "Matriz"),
                       avg_c, std_c,
                       avg_b, std_b,
                       avg_d, std_d);
            }
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("Fim dos testes. Use Cat para comparar impacto da densidade.\n");
}

int main() {
    srand(42); // semente fixa para reprodutibilidade
    run_performance_tests();
    return 0;
}
