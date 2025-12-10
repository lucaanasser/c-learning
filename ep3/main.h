
#ifndef _MAIN_H
#define _MAIN_H

enum opcoes
{
    CARREGAR_SER    = 'c' /* carregar lista de filmes (Sem Eliminar Repeticoes)*/
    ,CARREGAR_ER     = 'C' /* carregar lista de filmes (Eliminando Repeticoes) */
    ,PROCURAR        = 'p' /* procurar filme */
    ,HASH            = 'h' /* inserir palavras em nomes de filmes na TS */ 
    ,PROCURAR_HASH   = 'P' /* procurar um filme atraves da TS */ 
    ,MOSTRAR_HASH    = 'M' /* mostrar a TS */ 
    ,LIMPAR_HASH     = 'L' /* limpar a TS */
    ,INSERIR         = 'i' /* inserir filme */
    ,REMOVER         = 'r' /* remover filme */
    ,ORDENAR_NOME_M  = 'o' /* ordenar lista de filmes por nome (merge) */
    ,ORDENAR_NOTA_Q  = 'q' /* ordenar lista de filmes por nota (quick) */
    ,MOSTRAR         = 'm' /* mostrar filmes */
    ,MOSTRAR_MENOR   = '<' /* melhores filmes com nota menor que ... */
    ,MOSTRAR_MAIOR   = '>' /* piores filmes com nota maio que ... */
    ,LIMPAR          = 'l'  /* limpar a lista de filmes */
    ,SAIR            = 'x' /* sair do programa */
};

#endif
