#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void VerificaAcerto( char chave[], char tentativa[], int n){
    int contaerros = 0;
    for (int i = 0; i < n && contaerros == 0; i++){  
        if(chave[i] != tentativa[i]){  
          contaerros++;  
        }
    } 
    
    if(contaerros == 0){  
            printf("Você acertou\n");  
        }else{ printf("Você errou\n"); }
}

char* SelecionaPalavra(int tamanho){
  if(tamanho == 4){
    return "casa";  
  }
  else if(tamanho == 6){
    return "amigos";  
  }
  else if(tamanho == 8){
    return "vermelho";  
  }
  else{
    return NULL;
  }
}  
 
int main() {
    int tamanho;
    printf ("Escolha com quantas letras quer jogar (4, 6, 8,): \n");
    scanf ("%d", &tamanho);
    
    char *tentativa = (char *) malloc((tamanho + 1 ) * sizeof(char));
    printf ("Qual sua primeira tentativa para a palavra de %d letras? \n", tamanho);
    scanf ("%s", tentativa);
    
    char* chave = SelecionaPalavra(tamanho);
    
    VerificaAcerto(chave, tentativa, tamanho);
    
    free(tentativa);
    
    return 0;

}

