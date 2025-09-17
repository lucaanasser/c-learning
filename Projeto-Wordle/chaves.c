#include <stdlib.h> 
#include "chaves.h"

char* SelecionaPalavra(int tamanho){
  int num;
  if(tamanho == 4){
    num = rand() % 4;
    const char *chave[] = {"casa", "caro", "gato", "rato"};
    return chave[num];  
  }
  else if(tamanho == 6){
    num = rand() % 3;
    const char *chave[] = {"utopia", "carros", "idiota"};
    return chave[num];
  }
  else if(tamanho == 8){
    num = rand() % 4;
    const char *chave[] = {"respeito", "pandemia", "abstrato", "devaneio"};
    return chave[num];
  }
  else{
    return NULL;
  }
}  
