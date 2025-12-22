# include <stdio.h>
# include "random.h"

void counting_sort_mask(int A[], int n,int bpdigit,int bshift) {
	

	//int k = 0; for (int i = 0; i < n; i++) if (A[i] > k) k = A[i]; // calcula k
	int k = 1 << bpdigit; // calcula k
	int mask = (k - 1) << bshift;
	int B[k];
	for (int i = 0; i < k; i++) B[i] = 0; // zera o vetor B
	for (int j = 0; j < n; j++) B[((A[j] & mask)>>bshift)]++; // conta o número de ocorrências de cada valor, no final, B[i] é precisamente o número de ocorrências de i em A
	for (int i = 1; i < k; i++) B[i] = B[i-1] + B[i];
	
	int C[n];
	for (int i = n-1; i >= 0; i--) {
		C[B[((A[i] & mask) >> bshift)]-1] = A[i]; // ex C[B[A[30]]-1] = C[B[3]-1] = C[15-1] = C[14] = 3
		B[((A[i] & mask) >> bshift)]--;
	}
	
	for (int i = 0; i < n; i++) A[i] = C[i];
}

void radix_sort(int A[], int n) {
	int bpdigits = 4;
	for (int i = 0; i < 16; i = i+bpdigits) 
	counting_sort_mask(A,n,bpdigits,i);
}

void binary(int x,int n) {
	for (int i = 0; i < n; i++) {
		printf("%d, ", x & (1 << i));		
	}
	printf("\n");
}

void testa_se_e_crescente(int A[],int n) {
	for (int i = 0; i < n-1; i++) {
		if (A[i] > A[i+1]) {
			printf("NÃO ESTÁ ORDENADO\n");
			return;
		}
	}
	printf("Está ordenado, pode bater palmas\n");
}

void main() {



int n = 20;
//int k = 65500;
//int* A = malloc(n*sizeof(int));
float* A = malloc(n*sizeof(float));

random_vec_01(A,n);
print_vec_01(A,n);

for (int i = 0; i < n; i++) printf("%f %d\n",A[i],(int) (n*A[i]));

//radix_sort(A,n);
//print_vec_01(A,n);

//testa_se_e_crescente(A,n);

}
