#include <stdlib.h>
#include <time.h>

void random_vec(int v[], int n, int m) {
  srand(time(NULL));  // seed with current time
	for (int i = 0; i < n; i++) {
		v[i] = rand() % m;
	}
}

void random_vec_01(float v[], int n) {
  srand(time(NULL));  // seed with current time
	for (int i = 0; i < n; i++) {
		v[i] = rand()/(float)RAND_MAX;
	}
}

void print_vec(int v[], int n) {
	printf("[");
	for (int i = 0; i < n-1; i++) {
		printf("%d, ",v[i]);
	}
	printf("%d]\n",v[n-1]);
	
}

void print_vec_01(float v[], int n) {
	printf("[");
	for (int i = 0; i < n-1; i++) {
		printf("%f, ",v[i]);
	}
	printf("%f]\n",v[n-1]);
	
}
