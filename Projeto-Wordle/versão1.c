#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SomaR(int v[], int n){
    if (n == 0){
        return 0;
    }
    else{
        int x = SomaR(v, n - 1);

        if(v[n-1] > 0){
            x += v[n-1];
        }
        return x;

    }

}

void main() {
    srand(time(NULL));

    int v[10];
    int n = 10;

    for (int i = 0; i < n; i++) {
        v[i] = (rand() % 201) - 100;
        printf(" %d", v[i]);
    }
   
   int soma = SomaR(v, n);
   printf ("\nA soma positiva é: %d", soma);

}
