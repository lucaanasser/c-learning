# include <stdio.h>
# include "random.h"

void counting_sort(int A[], int n) {
	int k = 0; for (int i = 0; i < n; i++) if (A[i] > k) k = A[i]; // calcula k
	
	int B[k];
	for (int i = 0; i < k; i++) B[i] = 0; // zera o vetor B
	for (int j = 0; j < n; j++) B[A[j]]++; // conta o número de ocorrências de cada valor, no final, B[i] é precisamente o número de ocorrências de i em A
	for (int i = 1; i < k; i++) B[i] = B[i-1] + B[i];
	
	int C[n];
	for (int i = n-1; i >= 0; i--) {
		C[B[A[i]]-1] = A[i]; // ex C[B[A[30]]-1] = C[B[3]-1] = C[15-1] = C[14] = 3
		B[A[i]]--;
	}
	
	for (int i = 0; i < n; i++) A[i] = C[i];
}

void main() {

	int n = 10;
	int k = 100;
	int* A = malloc(30*sizeof(int));
	//int A[30];
	random_vec(A, n, k);
	
	printf("A = ");
	print_vec(A,n);
		
}
