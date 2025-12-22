# include <stdio.h>
# include <stdlib.h>
#include <time.h>
# include "lista_encadeada.h"
# include "random.h"

# define m_def 1000
# define p_def 1009

typedef struct {
	celula** table;
	int a, b, m, p;
} hash_table;

typedef int my_object;

void adicionar_hash(hash_table* ht, int key) {
	int hash = ((((ht->a)*key + ht->b) % ht->p) % ht->m); // calcula h(x) = ((ax + b) mod p) mod m
	(ht->table)[hash] = adicionar_LE((ht->table)[hash],key); //adiciona key na posição h(x) de ht
}

celula* busca_hash(hash_table* ht, int key) {
	int hash = ((((ht->a)*key + ht->b) % ht->p) % ht->m); // calcula h(x) = ((ax + b) mod p) mod m
//	return busca_LE((ht->table)[hash],key); //adiciona key na posição h(x) de ht
}

hash_table* create_hashing_table(int m,int p) {
	srand(time(NULL));  // seed with current time
	hash_table* ht = malloc(sizeof(hash_table));
	ht->table = malloc(m*sizeof(celula*));
	ht->a = (rand() % (p-1)) + 1;
	ht->b = rand() % p;
	ht->m = m;
	ht->p = p;
	return ht;
}

void main() {
	srand(time(NULL));  // seed with current time
	int m = 10;
	int p = 13;
	int U = 10000;
	
	int n = 20;
	
	hash_table* ht = create_hashing_table(m,p);

	int v[] = {2596, 3378, 1177, 1821, 4046, 9849, 3926, 4530, 5481, 5888, 7879, 3796, 2294, 4825, 9870, 8875, 5710, 1086, 3274, 186};
	
	for (int i = 0; i < n; i++) {
		adicionar_hash(ht,v[i]);
	}
	
	for (int i = 0; i < ht->m; i++) {
		printf("%d: ",i);
		imprime_LE(ht->table[i]);
	}
	
//	int* v = malloc(n*sizeof(int));
//	random_vec(v,n,U);
//	print_vec(v,n);
}
