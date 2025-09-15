#include <stdio.h> 
/* A função recebe um inteiro n > 0 e devolve a piso de log(n) na base 2*/
int log (int n){
	int i;
	/* n_original = n_atual . 2^i */
	for (i = 0; n > 1; i++)
	{
		n /= 2;
	}
	return i;
}

void main(){
	int n = 30;
	for (int i = 1; i < n; i++){
		printf("%d \t %d\n", i, log(i));
	}

}
