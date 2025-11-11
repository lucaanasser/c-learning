#include <stdio.h>
#include <stdlib.h>

/* a) Implementar uma funcao que retorna exclui todos os valores repetidos e uma
* lista, por exemplo, se a lista tem os valores (1,1,2,2,3,4,1,4) a funcao deve
* retornar uma lista (1,2,3,4). */    


typedef struct no{
  int data;
  struct no *prox;
}lista;

lista* criaLista() {
  lista *nova_lista = NULL;
  return nova_lista;
}

lista* criaNo(int data) {
  lista *nova_lista = malloc(sizeof(lista));
  nova_lista->data = data;
  nova_lista->prox = NULL;
  return nova_lista;
}

void insereNo(lista **head, int data) {
  lista *inserir = criaNo(data);
  inserir->prox = *head;
  *head = inserir;
}

void removeRepeticao(lista **A) {  
  if (*A == NULL) return;  
  
  lista *aux_1 = *A;
  lista *aux_2 = *A;  
  while (aux_1 != NULL) { 
    while (aux_2 != NULL) {
      if (aux_2->prox == NULL) {
        break;
      }
      if (aux_1->data == aux_2->prox->data){
        lista *remove_2 = aux_2->prox;  
        aux_2->prox = aux_2->prox->prox;
        free(remove_2);
      } else {
        aux_2 = aux_2->prox;       
      }
    }
    aux_1 = aux_1->prox;
    aux_2 = aux_1;
  }
}

void printLista(lista *head) {
  printf("Lista: ");
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->prox;
  }
  printf("\n");
}

void liberaLista(lista **head) {
  while (*head != NULL) {
    lista *temp = *head;
    *head = (*head)->prox;
    free(temp);
  }
}

int main() {
  lista *lista1 = criaLista();
  
  printf("=== TESTE 1 ===\n");
  insereNo(&lista1, 4);
  insereNo(&lista1, 1);
  insereNo(&lista1, 4);
  insereNo(&lista1, 3);
  insereNo(&lista1, 2);
  insereNo(&lista1, 2);
  insereNo(&lista1, 1);
  insereNo(&lista1, 1);
  
  printf("Antes: ");
  printLista(lista1);
  removeRepeticao(&lista1);
  printf("Depois: ");
  printLista(lista1);
  printf("Esperado: 1 2 3 4\n\n");
  
  liberaLista(&lista1);
  
  printf("=== TESTE 2 ===\n");
  
  insereNo(&lista1, 3);
  insereNo(&lista1, 3);
  insereNo(&lista1, 3);
  insereNo(&lista1, 2);
  insereNo(&lista1, 2);
  insereNo(&lista1, 1);
  
  printf("Antes: ");
  printLista(lista1);
  removeRepeticao(&lista1);
  printf("Depois: ");
  printLista(lista1);
  printf("Esperado: 1 2 3\n\n");
  
  liberaLista(&lista1);
  
  printf("=== TESTE 3 ===\n");
  insereNo(&lista1, 5);
  insereNo(&lista1, 4);
  insereNo(&lista1, 3);
  insereNo(&lista1, 2);
  insereNo(&lista1, 1);
  
  printf("Antes: ");
  printLista(lista1);
  removeRepeticao(&lista1);
  printf("Depois: ");
  printLista(lista1);
  printf("Esperado: 1 2 3 4 5\n\n");
  
  liberaLista(&lista1);
  
  printf("=== TESTE 4: Um elemento ===\n");
  insereNo(&lista1, 7);
  
  printf("Antes: ");
  printLista(lista1);
  removeRepeticao(&lista1);
  printf("Depois: ");
  printLista(lista1);
  printf("Esperado: 7\n\n");
  
  liberaLista(&lista1);
  
  printf("=== TESTE 5 ===\n");
  insereNo(&lista1, 5);
  insereNo(&lista1, 5);
  insereNo(&lista1, 5);
  insereNo(&lista1, 5);
  
  printf("Antes: ");
  printLista(lista1);
  removeRepeticao(&lista1);
  printf("Depois: ");
  printLista(lista1);
  printf("Esperado: 5\n\n");
  
  liberaLista(&lista1);
  
  printf("=== TESTE 6 ===\n");
  printf("Antes: ");
  printLista(lista1);
  removeRepeticao(&lista1);
  printf("Depois: ");
  printLista(lista1);
  printf("Esperado: (vazia)\n\n");
  
  return 0;
}