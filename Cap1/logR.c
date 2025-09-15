#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SomaDigito(int n){
    if (n == 0){
        return 0;
    }
    else{
        return n % 10 + SomaDigito(n/10);          
    }

}

int main() {
    srand(time(NULL));
    int n = rand() % 10001;
   
    int soma = SomaDigito(n);
    printf ("\nO número é: %d e a função piso de seu log na base 2 é: %d", n, soma);
  return 1;
}
