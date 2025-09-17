#ifndef VERIFICATENTATIVA_H
#define VERIFICATENTATIVA_H

struct verifica {
    int estaErrado;
    int posicao;
    char letra;
    struct verifica *prox;
};

struct verifica* VerificaTentativa(char* chave, char* tentativa, int tamanho);

#endif