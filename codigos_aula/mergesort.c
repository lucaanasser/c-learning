# include <stdio.h>
# include <stdlib.h>
# include "random.h"
# include <unistd.h>

int* Combina(int A[], int nA, int B[], int nB) {
	int *C = malloc((nA+nB)*sizeof(int));
	
	int i = 0; int j = 0; int k = 0;
	
	while ((i < nA) && (j < nB)) {
		if (A[i] < B[j]) {
			C[k] = A[i];
			k++; i++;
			}
		else {
			C[k] = B[j];
			k++; j++;
		}
	}
	
	while (i < nA) {
			C[k] = A[i];
			k++; i++;		
	}
	
	while (j < nB) {
			C[k] = B[j];
			k++; j++;		
	}
	return C;
}

void merge_sort(int v[], int n) {
	
	if (n == 1) return;
	
	int meio = n/2;
	
	int *A = malloc(meio*sizeof(int));
	int *B = malloc((n-meio)*sizeof(int));
	for (int i = 0; i < meio; i++)	A[i] = v[i];
	for (int i = 0; i < n-meio; i++) B[i] = v[meio + i];

	merge_sort(A,meio);
	merge_sort(B,n-meio);
	int *C = Combina(A,meio,B,n-meio);
	for (int i = 0; i < n; i++) v[i] = C[i];
}

/*
void Combina_inloco(int v[], int p, int q, int r) {

	int i = p; int j = q; int k = p;
	
	while ((i < nA) && (j < nB)) {
		if (A[i] < B[j]) {
			C[k] = A[i];
			k++; i++;
			}
		else {
			C[k] = B[j];
			k++; j++;
		}
	}
	
	while (i < nA) {
			C[k] = A[i];
			k++; i++;		
	}
	
	while (j < nB) {
			C[k] = B[j];
			k++; j++;		
	}
	return C;
}
*/

void insertion_sort(int A[], int n) {
	for (int j = 1; j < n; j++) {
		int key = A[j];
		int i = j-1;
		while (i >= 0 && A[i] > key) {
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

void main() {

// Testes de merge_sort
int n = 400000;
int *v = malloc(n*sizeof(int));
random_vec(v,n,5000);
//print_vec(v,n);

int *v_copy = malloc(n*sizeof(int));
for (int i = 0; i < n; i++) v_copy[i] = v[i];

clock_t inicio = clock();
insertion_sort(v_copy,n);
printf("Tempo de ordenar com insertion sort: %Lf\n",(clock()-inicio)/(long double) CLOCKS_PER_SEC);

inicio = clock();
merge_sort(v,n);
printf("Tempo de ordenar com merge sort: %Lf\n",(clock()-inicio)/(long double) CLOCKS_PER_SEC);

//print_vec(v,n);

// Testes de Combina
/*
	int nA = 5;
	int *A = malloc(nA*sizeof(int));
	random_vec(A,nA,30);
	insertion_sort(A,nA);
	sleep(3);
	int nB = 7;
	int *B = malloc(nB*sizeof(int));
	random_vec(B,nB,30);
	insertion_sort(B,nB);
	
	int *C = Combina(A,nA,B,nB);
	
	print_vec(A,nA); print_vec(B,nB); print_vec(C,nA+nB);
*/
}
