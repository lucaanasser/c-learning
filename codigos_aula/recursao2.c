# include <stdio.h>

int subvetor_soma_maxima(int A[], int n) {
	
	int soma_max;
	soma_max = 0;
	
	for (int ini = 0; ini < n; ini++) {
		int soma_local = 0;
		for (int fim = ini+1; fim < n+1; fim++) {
			soma_local += A[fim-1];
			if (soma_local > soma_max) 
				soma_max = soma_local;
		}
	}	
	return soma_max;
}


int subvetor_soma_maxima_R1(int A[], int n) {
	
	if (n == 0) return 0;
	
	// soluções que contêm A[n-1]
	int soma_max = 0;
	int soma = 0;
	for (int ini = n-1; ini >= 0; ini--) {
		soma += A[ini];
		if (soma > soma_max) soma_max = soma;
	}
	
	int subvetor_max_rec = subvetor_soma_maxima_R1(A,n-1); // soluções que não contêm A[n-1]
	
	if (soma_max > subvetor_max_rec) return soma_max;
	return subvetor_max_rec;
}

int subvetor_soma_maxima_R2(int A[], int ini, int fim) {
	
	if (fim <= ini) return 0;
	
	int meio = (ini+fim)/2;
	
	// soma máxima da esquerda
	int soma_max_esq = 0;
	int soma = 0;
	for (int i = meio; i >= ini; i--) {
		soma += A[i];
		if (soma > soma_max_esq) soma_max_esq = soma;
	}
	// soma máxima da direita
	int soma_max_dir = 0;
	soma = 0;
	for (int i = meio+1; i < fim; i++) {
		soma += A[i];
		if (soma > soma_max_dir) soma_max_dir = soma;
	}
	
	int soma_meio = soma_max_dir + soma_max_esq;
	
	// chamadas recursivas
	int soma_rec_esq = subvetor_soma_maxima_R2(A,ini,meio);
	int soma_rec_dir = subvetor_soma_maxima_R2(A,meio+1,fim);
	
	if ((soma_meio > soma_rec_esq) && (soma_meio > soma_rec_dir)) return soma_meio;
	if (soma_rec_esq > soma_rec_dir) return soma_rec_esq;
	return soma_rec_dir;
	
	
	
	
	
}


void main() {
	int A[] = {13,-3,5,-17,22,89,-129318273,-23,17,-17,0,108,};
	int minha_soma = subvetor_soma_maxima_R2(A,0,12);
	printf("A minha soma deu %d\n",minha_soma);
}
