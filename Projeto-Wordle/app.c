#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chaves.h"
#include "verificaTentativa.h"

int main() {
    srand(time(NULL));

    int tamanho;
    printf("Escolha com quantas letras quer jogar (4, 6, 8): \n");
    scanf("%d", &tamanho);
    
    char* chave = SelecionaPalavra(tamanho);
    if(chave == NULL){
      printf("Tamanho invalido");
      return -1;
    }
    
    char *tentativa = (char *) malloc((tamanho + 1 ) * sizeof(char));
    printf ("Qual sua primeira tentativa para a palavra de %d letras? \n", tamanho);
    scanf ("%s", tentativa);
    VerificaTetativa(chave, tentativa, tamanho);
    free(tentativa);

    return 0;
}