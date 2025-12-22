# include <stdio.h>
# include <stdlib.h>

int string_search_trivial(char* a, int m, char* b, int n) {
	
	int k, r, ocorrs;
	ocorrs = 0;
	
	for (k = m; k <= n; k++) {
		r = 0;
		while (r < m && a[m-1-r] == b[k-1-r]) r++;
		if (r >= m) ocorrs++;
	}
	return ocorrs;
}

int boyer_moore_1(char* a, int m, char* b, int n) {
	int T1[256],i,k,r,ocorrs;
	// Pre-processamento da palavra a, criação de T1
	for (i = 0; i < 256; i++) T1[i] = m;
	for (i = 0; i < m; i++) T1[a[i]] = m-1-i;
	
	ocorrs = 0; k = m-1;
	while (k < n) {
		printf("%d, ",k);
		r = 0;
		while (r < m && a[m-1-r] == b[k-1-r]) r++;
		if (r >= m) ocorrs++;
		if (k == n) k += 1;
		else k += T1[b[k+1]]+1;
	}
	return ocorrs;
}

void main() {

	char* texto = "Fabio eh muito legal, legal mesmo viu, bem legal";
	char* palavra = "legal";
	
	printf("O número de ocorrências é %d\n", boyer_moore_1(palavra,5,texto,48));
	
}
