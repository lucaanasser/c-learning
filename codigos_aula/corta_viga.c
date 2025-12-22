# include <stdio.h>
# include <stdlib.h>

int corta_viga1(int n, int p[], int* contador) {

	(*contador)++;

	if (n == 1) return p[1];

	int lucro_max = p[n];
	for (int i = 1; i <= n/2; i++) {
		int max_esq = corta_viga1(i,p, contador);
		int max_dir = corta_viga1(n-i,p, contador);
		int lucro_i = max_esq + max_dir;
		
		if (lucro_i > lucro_max) lucro_max = lucro_i;
	}
	
	return lucro_max;
}

int corta_viga2(int n, int p[], int* contador) {

	if (n == 5) (*contador)++;

	if (n == 1) return p[1];

	int lucro_max = p[n];
	for (int i = 1; i <= n/2; i++) {
		int lucro_i = p[i] + corta_viga2(n-i,p, contador);
		
		if (lucro_i > lucro_max) lucro_max = lucro_i;
	}
	
	return lucro_max;
}

int corta_viga2_memorizado(int n, int p[], int* contador,int memoria[]) {

	(*contador)++;
	
	if (memoria[n] != -1) return memoria[n];

	if (n == 1) return p[1];

	int lucro_max = p[n];
	for (int i = 1; i <= n; i++) {
		int lucro_i = p[i] + corta_viga2_memorizado(n-i,p, contador, memoria);
		
		if (lucro_i > lucro_max) lucro_max = lucro_i;
	}
	
	memoria[n] = lucro_max;
	
	return lucro_max;
}

int corta_viga_bottom_up(int n, int p[]) {
	int *max_lucro = malloc((n+1)*sizeof(int));
	
	
	for (int i = 1; i <= n; i++) {
		// Calcula max_lucro[i]
		max_lucro[i] = p[i];
		for (int j = 1; j <= i/2; j++) {
			int candidato = max_lucro[j] + max_lucro[i-j];
			if (candidato > max_lucro[i]) max_lucro[i] = candidato;
		}
	}
	
	return max_lucro[n];
}


void main() {
	int contador = 0;

	int n = 300;

	int *p = (int*) malloc((n+1)*sizeof(int));
	p[0] = 0; p[1] = 1; p[2] = 3; p[3] = 2;
	for (int i = 4; i <= n+1; i++) p[i] = 0;
	
	int *memoria = (int*) malloc((n+1)*sizeof(int));
	for (int i = 0; i <= n; i++) memoria[i] = -1;
	
	//int lucro_max = corta_viga2_memorizado(n,p, &contador,memoria);
	int lucro_max = corta_viga_bottom_up(n,p);
	printf("O lucro máximo é %d\n", lucro_max);
	printf("O número de chamadas foi %d\n", contador);
	return;
}
