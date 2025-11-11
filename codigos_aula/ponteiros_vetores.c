# include <stdio.h>

void modifica_vetor(int v[], int pos, int x) {
	v[pos] = x;
}

void imprime(int v[], int n) {
	printf("[");
	for (int i = 0; i < n-1; i++) {
		printf("%d, ",v[i]);
	}
	printf("%d]\n\n",v[n-1]);
}

void imprime_endereços(int v[], int n) {
	for (int i = 0; i < n; i++) {
		printf("O endereço de v[%d] é %p\n",i,&v[i]);
	}
}

void main() {

int v[] = {3,5,7,11,13,17};


imprime(v,6);
/*
modifica_vetor(v,3,19);
imprime(v,6);
*/

for (int i = 0; i < 6; i++) {
	printf("o %d-ésimo endereço é %p\n",i,(v+i));
}

imprime_endereços(v,6);	

	printf("\n\no endereço curioso é %p\n",(v-1));

}
