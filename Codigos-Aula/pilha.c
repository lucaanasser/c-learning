# include <stdio.h>

typedef struct {
	char nome[100];
	int idade;
} Pessoa;

typedef Pessoa meu_objeto;

typedef struct Pilha {
	meu_objeto dados[100];
	int tam;
} Pilha ;

void empilhar(Pilha *P, meu_objeto x) {
	P->dados[P->tam] = x;
	P->tam++;
}

meu_objeto desempilhar(Pilha *P) {
	if (P->tam == 0) {
		Pessoa nula;
	return nula;
	}
	
	meu_objeto resultado = P->dados[P->tam-1];
	P->tam--;
	return resultado;
}


int main() {
	Pilha P;
	P.tam = 0;

	Pessoa fabio = {"Fabio",26};
	Pessoa joel = {"Joel",31};
	Pessoa isaque = {"Isaque", 79};
	
	
	empilhar(&P,fabio);
	empilhar(&P,joel);
	empilhar(&P,isaque);
	
	printf("o tamanho da pilha agora é %d\n\n", P.tam);
	
	while (P.tam > 0) {
		meu_objeto x = desempilhar(&P);
		printf("%s tem %d anos ,\n",x.nome,x.idade);
	}
	printf("\n");
	
	return 0;
}
