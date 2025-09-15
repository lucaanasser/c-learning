#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int min;
    int max;
} MinMax;

MinMax MinMaxR(int v[], int n) {
    if (n == 1) {
        MinMax mm;
        mm.min = v[0];
        mm.max = v[0];
        return mm;
    }

    MinMax mm = MinMaxR(v, n - 1);

    if ( mm.min > v[n - 1]) { 
    	mm.min = v[n - 1];
    }
    if (mm.max < v[n - 1]) {
    	mm.max = v[n - 1];
    }
    return mm;
}

void main() {
    srand(time(NULL));

    int v[10];
    int n = 10;

    for (int i = 0; i < n; i++) {
        v[i] = rand() % 101;
        printf("%d ", v[i]);
    }

    MinMax mm = MinMaxR(v, n);
    int dif = mm.max - mm.min;

    printf("\nDiferença: %d\n", dif);

}
