# include <stdio.h>

int soma(int a, int b) {
	return a+b;
}

int multiplicacao(int a, int b) {
	return a*b;
}

void main() {
	
	int x = 10;
	
	int (*p[])(int,int) = {soma,multiplicacao};
	
	for (int i = 0; i < 2; i++) {
		printf("O valor de x é %d\n", p[i](20,30));
	}
	
	/*
	printf("Os endereços são\n  %p e\n %p\n",p,soma);
	*/
}
