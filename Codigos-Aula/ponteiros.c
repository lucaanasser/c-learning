# include <stdio.h>

typedef struct {
	char nome[100];
	int idade;
} Pessoa;

void aniversario(Pessoa *x) {
	printf("Ontem %s tinha %d anos\n",x->nome, x->idade);
	(*x).idade++;
	printf("Hoje %s faz %d anos\n",(*x).nome, (*x).idade);
	printf("Parabéns %s!!!\n\n",(*x).nome);
}

void aniversario_surpresa(Pessoa x) {
	printf("O endereço de x é %p\n", &x);

	printf("Ontem %s tinha %d anos\n",x.nome, x.idade);
	x.idade++;
	printf("Hoje %s faz %d anos\n",x.nome, x.idade);
	printf("Parabéns %s!!!\n\n",x.nome);
}

void troca_valores(int *x, int *y) {
	int aux = *x;
	*x = *y;
	*y = aux;
}

void main() {




Pessoa fabio = {"Fábio", 25};
printf("O endereço de %s é %p\n",fabio.nome, &fabio);
aniversario_surpresa(fabio);
/*
printf("%s tem %d anos\n", fabio.nome, fabio.idade);

aniversario(&fabio);

printf("Agora %s tem %d anos\n", fabio.nome, fabio.idade);
*/

/*
int a = 20;
int* p = &a;
printf("p = %p e *p = %d\n", p, *p);
printf("&a = %p\n", &a);
int q = *p;
*/
/*
int a = 10;
int b = 35;

printf("O endereço de a é %p, \ne o endereço de b é %p\n", &a, &b);
printf("a = %d e b = %d\n", *&a, *&b);

printf("a = %d e b = %d\n", a, b);
troca_valores(&a,&b);	
printf("a = %d e b = %d\n", a, b);
*/
}
