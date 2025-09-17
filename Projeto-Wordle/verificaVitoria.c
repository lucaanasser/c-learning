#include <stdio.h>
#include <stdlib.h>

#include "verificaTentativa.h"

void VerificaVitoria(struct verifica *cabeca, char chave[]){
    struct verifica *verificado = cabeca;
    struct verifica *atual = verifica;
    int contaErros = 0;
    
    while(atual != NULL){
      if(atual->estaErrado != 0){
        contaErros++;
        atual = atual->prox;
      }
    }
    if(contaErros == 0){
      printf("Voce acertou, parabens!")
    }else { geraDica()
    return (contaErros == 0) ? 1 : 0;
}
