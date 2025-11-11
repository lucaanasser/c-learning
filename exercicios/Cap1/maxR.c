#include <stdio.h> 
#include <time.h>
#include <stdlib.h>

int MaxR(int v[], int n) {
    if( n == 1){
        return v[0];
    }else{
        int x;
        x = MaxR(v, n - 1);
        if (x > v[n-1]){
            return x;
        }else{
            return v[n-1];
        }
    }
}

int testaMaxR (int v[], int n) {
    int j, x = v[0];
    for (j = 1; j < n; j++) {
        if (x < v[j]) {
            x = v[j];
        }
    }
    return x;
}

int main() {

    srand(time(NULL));

    int v[10];
    int n = 10;

    for (int i = 0; i < 10; i++) {
        v[i] = rand() % 101;   
    }

    for (int i = 0; i < 10; ++i) {
        int k = v[i];
        printf("%d; ", k);
    }

    int x = MaxR(v, n);

    int y = testaMaxR(v, n);

    printf("recursivo: %d; esperado: %d", x, y);

    return 0;

}

