# include <stdio.h>
# include <stdlib.h>
# include "random.h"
# include <unistd.h>

int partition(int A[],int p, int r) {
	
	int i = p; 
	int buffer;
	
	for (int k = p; k < r-1; k++) {
		if (A[k] < A[r-1]) {
			buffer = A[i];
			A[i] = A[k];
			A[k] = buffer;
			i++;
		}
	}
	buffer = A[i];
	A[i] = A[r-1];
	A[r-1] = buffer;
	
	return i;
}

int random_partition(int A[],int p, int r) {
	int i = (rand() % (r-p)) + p; // escolhe novo índice aleatório para o pivot
	int buffer = A[i];
	A[i] = A[r-1];
	A[r-1] = buffer;
	return partition(A,p,r);
}

void quicksort(int A[], int p, int q) {

	if (q <= p + 1) return;

	int r = partition(A,p,q);
	quicksort(A,p,r);
	quicksort(A,r+1,q);
}

void random_quicksort(int A[], int p, int q) {

	if (q <= p + 1) return;

	int r = random_partition(A,p,q);
	random_quicksort(A,p,r);
	random_quicksort(A,r+1,q);
}

int main() {

int n = 705032704-1;
int *v = malloc(n*sizeof(int));
random_vec(v,n,705032704-1);
//print_vec(v,n);

//int r = partition(v,0,n);
//print_vec(v,n);

quicksort(v,0,n);
//print_vec(v,n);
	
	return 0;
}
