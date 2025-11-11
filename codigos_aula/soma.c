# include <stdio.h>

int soma(int lista[], int n) {
	
	if (n == 1) { 
		return lista[0];
	}
	
	int minha_soma = lista[n-1] + soma(lista, n-1);
	
	return minha_soma
}
	


void main() {
	int A[] = {0,7,2,20,9};
	
	printf("A soma é %d\n",soma(A,5));
}
