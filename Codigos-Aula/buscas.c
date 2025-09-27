# include <stdio.h>

int BuscaLinear(int A[], int n, int x) {
	
	for (int i = 0; i < n; i++) {
		if (A[i] == x) return i;
	}
	return -1;
}

int BuscaBinaria(int A[], int n, int x) {
	int esq = 0;
	int dir = n-1;
	int meio;
	
	while (esq <= dir) {
		meio = (esq + dir)/2;
		if (A[meio] == x) return meio;	
		if (x < A[meio]) dir = meio - 1;
		else esq = meio + 1;
	}
	return -1;
}	

void main() {
	int A[] = {2,3,5,7,11,13,17,19,23};
	int x = 11;
	int posBL = BuscaLinear(A,9,x);
	int posBB = BuscaBinaria(A,9,x);
	
	printf("O %d está na posição %d\n\n", x, posBL);
	printf("O %d está na posição %d\n\n", x, posBB);
}
