# include <stdio.h>

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
	int A[] = {9,5,1,8,12,45,-3};
	insertion_sort(A,7);
	printf("[");
	for (int i = 0; i < 7; i++) {
		printf("%d,",A[i]);
	}
	printf("]");
	printf("\n");
}
