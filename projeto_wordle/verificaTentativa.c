#include <stdio.h>
#include "VerificaTentativa.h"

struct verifica{
    int estaErrado;
    int posicao;
    char letra;
    struct verifica *prox;
};

struct verifica*  criarNo(int estaErrado, int posicao, char letra) {
    struct verifica *novoNo = (struct verifica*) malloc(sizeof(struct verifica));
    novoNo->estaErrado = estaErrado;
    novoNo->posicao = posicao;
    novoNo->letra = letra;
    novoNo->prox = NULL;
    return novoNo;
}

void VerificaTentativa(char chave[], char tentativa[], int tamanho){
    struct verifica *cabeca = NULL;
    struct verifica *rabo = NULL;

    for (int i = 0; i < tamanho; i++) {
      struct verifica *novoNo = criarNo(chave[i] != tentativa[i], i, tentativa[i]);
      if (cabeca == NULL) {     
        cabeca = novoNo;        
        rabo = novoNo;          
      } else {                    
            rabo->prox = novoNo;    
            rabo = novoNo;          
        }
    }
    
    verificaVitoria(cabeca, chave);
}
