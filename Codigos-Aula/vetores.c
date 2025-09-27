# include <stdio.h>
# define N 100

/* Recebe um número x e um vetor v[0..n-1], 
	e devolve k tal que 
	v[k] = x, ou -1 se x não estiver em v[0..n-1] */
int Busca(int x, int v[], int n) {
	int k;
	k = n-1;
	while (k >= 0 && v[k] != x)
		k -= 1;
	return k;
}

int BuscaArriscada(int x, int v[], int n) {
	int k;
	k = n-1;
	while (v[k] != x && k >= 0)
		k -= 1;
	return k;
}

int BuscaR(int x, int v[], int n) {
	if (n == 0) return -1;
	if (x == v[n-1]) return n-1;
	return BuscaR(x,v,n-1);
}

/* Remove o elemento de índice k do vetor v[0..n-1]
devolve o novo valor n */
int Remove(int k, int v[], int n) {
	int j;
	for (j = k; j < n-1; j++)
		v[j] = v[j+1];
	return n-1;
}

int RemoveR(int k, int v[], int n) {
	if (k == n-1) return n-1;
	else{
		v[k] = v[k+1];
		return RemoveR(k+1,v,n);
	}
}

int Insere(int k, int y, int v[], int n) {
	int j;
	for (j = n; j > k; j--)
		v[j] = v[j-1];
	v[k] = y;
	return n+1;
}

int InsereR(int k, int y, int v[], int n) {
	if (k == n) v[n] = y;
	else {
		v[n] = v[n-1];
		InsereR(k,y,v,n-1);
	}
	return n+1;
}

void print_lista(int v[], int n) {
	printf("[");
	for (int i = 0; i < n-1; i++) {
		printf("%d, ",v[i]);
	}
	printf("%d]\n",v[n-1]);
}

int RemoveZeros(int v[], int n) {
	
	int i = 0, j; /* i é a posição de escrita, j é a posição de leitura */
	for (j = 0; j < n; j++) {
		printf("\nj = %d, i = %d\n",j,i);
		print_lista(v,n);

		if (v[j] != 0) {
			v[i] = v[j];
			i += 1;
		}
	}
	return i;
}

int RemoveZerosR(int v[], int n) {
	int i;
	if (n == 0) return 0;
	i = RemoveZerosR(v,n-1);
	if (v[n-1] == 0) return i;
	v[i] = v[n-1];
	return i+1;
}
void main() {
	/* int v[N];  v[0..n-1], 0 <= n <= N */
	
	int v[N] = {222,555,0,0,0,111,333,0,0,0,444,666,0,555,888,987,654,0,0,0,0,0};
	int n = 22;
	print_lista(v,n);
	/*n = RemoveR(4,v,n);*/
	n = RemoveZeros(v,n);
	print_lista(v,n);
	
}

int Busca_D1(int x, int v[], int n) {
	int k = n-1, achou = 0;
	while (k >= 0 && achou == 0) {/* deselegante */
		if (v[k] == x) achou = 1; /* deselegante */
		else k -= 1;
	}
	return k;
}

int Busca_I1(int x, int v[], int n) {
	int k = 0;
	int sol = -1;
	for (k = n-1; k >= 0; k--) { /* ineficiente */
		if (v[k] == x) {
		sol = k;
		break;					/* deselegante*/
		}
	}
	return sol;
}

