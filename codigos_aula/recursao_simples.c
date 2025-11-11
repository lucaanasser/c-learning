# include <stdio.h>

int maximo(int n, int lista[]) {
	
	if (n == 1) {
		return lista[0];
	}
	
	int submaximo = maximo(n-1,lista);
	if (lista[n-1] > submaximo) {
		return lista[n-1];
	}
	else {
		return submaximo;
	} 
}

int busca(int x, int n, int lista[]) {
	if (n == 0)	return -1;
	if (lista[n-1] == x) return n-1;
	else return busca(x,n-1,lista);
}

void main() {

	int minha_lista[] = {7,2,3,5,7,-10,100, 12};
	
	int x = 7;
	
	printf("O elemento %d está na %d-ésima casa da lista\n",x,busca(x,8,minha_lista));
	
	/*
	printf("O máximo da lista é %d\n",maximo(7,minha_lista));
	*/
}
