# include <stdio.h>
# include <stdlib.h>

typedef struct No No;

struct No {
	int valor;
	No* proximo[256];
	int numero_de_subnos;
};

int busca(No* raiz, char chave[]) {
	No* no_aux = raiz;
	int pos = 0;
	while (chave[pos] != '\0') {
		no_aux = (no_aux->proximo)[chave[pos]];
		if (no_aux == NULL) return -1;
		pos++;
	} 
	return no_aux->valor;
}

void adiciona(No* raiz, char chave[], int valor) {
	No* no_aux = raiz;
	int pos = 0;
	while (chave[pos] != '\0') {
		if ((no_aux->proximo)[chave[pos]] == NULL) {
			No* novo_no = malloc(sizeof(No));
			(novo_no->valor) = -1;
			(no_aux->proximo)[chave[pos]] = novo_no;
			(raiz->numero_de_subnos)++;
		}
		no_aux = (no_aux->proximo)[chave[pos]];
		pos++;
	} 
	(no_aux->valor) = valor;
}

void main() {
	No* D = malloc(sizeof(No));
	D->valor = -1;
	D->numero_de_subnos = 0;
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	
	adiciona(D,"Fábio", 26);
	adiciona(D,"Igor",12);
	adiciona(D,"Vitor",20);
	printf("Adicionei os três primeiso e a árvore tem %d subnós\n",D->numero_de_subnos);
	
	printf("Igor tem %d anos\n",busca(D,"Igor"));
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	printf("Fábio tem %d anos\n",busca(D,"Fábio"));
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	printf("Vitor tem %d anos\n",busca(D,"Vitor"));
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	
	adiciona(D,"Fábia", 212099);
	
	printf("Aleatório tem %d anos\n",busca(D,"Aleatório"));
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	
	printf("Fábia tem %d anos\n",busca(D,"Fábia"));
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	
	adiciona(D,"Fábio", 24);
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	
	printf("Fábio tem %d anos\n",busca(D,"Fábio"));
	printf("A árvore tem %d subnós\n",D->numero_de_subnos);
	
	adiciona(D,"Fernando", 91271081);
	printf("Depois de adicionar Fernando, a árvore tem %d subnós\n",D->numero_de_subnos);
}
