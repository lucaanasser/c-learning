/* Note que em todas minhas funcoes tive que declarar as variaveis
 no inicio do bloco, pois o C90 gera um warning caso voce declare
 variaveis misturadas com codigo. Alem disso, todo o loop for tambem
 nao pode receber declarações dentro dele, como "for (int i = 0; ...", em C90.
 Assim, para manter a compatibilidade com C90, fiz essas alterações. */


/*----------------------------------------------------------*/
/* filmes.h e a interface para as funcoes neste modulo      */
#include "filmes.h" 

/*----------------------------------------------------------*/
#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf() */ 
#include <string.h>  /* strlen(), strncpy(), strcmp(), strtok() */

#include "util.h"    /* Bool */
#include "iofilmes.h"
#include "st.h"      /* freeST(), initST(), putFilmeST(), getFilmeST(),
                        showST() */

/*----------------------------------------------------------------------
 *  crieFilme
 *
 *  Recebe informacoes sobre um filme 
 *
 *      - DIST  : distribuicao de notas
 *      - VOTOS : numero de votos
 *      - NOTA  : nota do filme 
 *      - ANO   : ano de producao do filme
 *
 *  e cria uma celula do tipo Filme para armazenar essa informacao. 
 *  A funcao retorna o endereco da celula criada.
 */
Filme *
crieFilme (char dist[], int votos, float nota, char *nome, int ano)
{
    int    len = strlen(nome) + 1; /* +1 para o '\0' */
    Filme *flm;

    flm = malloc(sizeof *flm);

    strncpy(flm->dist, dist, TAM_DIST+1); /* +1 para o '\0' */

    flm->votos = votos;
    flm->nota  = nota;

    flm->nome = malloc(len*sizeof(char));
    strncpy(flm->nome, nome, len);

    flm->ano  = ano;

    flm->prox = flm->ant = NULL; /* paranoia */

    return flm;
}

/*----------------------------------------------------------------------
 *  crieListaFilmes
 * 
 *  Cria uma estrutura que representa lista de filmes vazia.
 *  A funcao retorna o endereco dessa estrutura.
 *
 *  Um lista de filmes e representada por uma lista encadeada 
 *  duplamente ligada com cabeca. 
 */
ListaFilmes *
crieListaFilmes()
{
    ListaFilmes *nova_lista;
    Filme *cab;

    nova_lista = malloc(sizeof(ListaFilmes)); 
    if(nova_lista == NULL) return NULL;

    cab = malloc(sizeof(Filme));
    if(cab == NULL) {
        free(nova_lista);
        return NULL;
    }

    cab->prox = cab;
    cab->ant = cab;
    nova_lista->cab = cab;
    nova_lista->nFilmes = 0;

    return nova_lista;
}

/*----------------------------------------------------------------------
 *  libereListaFilmes(lst)
 *
 *  Recebe um ponteiro lst para uma estrutura que representa uma lista 
 *  de filmes e libera toda a memoria alocada para a lista.
 *
 *  Esta funcao utiliza a funcao libereFilme().
 */

void
libereListaFilmes(ListaFilmes *lst)
{
    Filme *cab;
    Filme *atual;
    Filme *prox;

    if(lst == NULL) return;

    cab = lst->cab;
    atual = cab->prox;

    while (atual != cab) {
        prox = atual->prox;
        libereFilme(atual);
        atual = prox;
    }

    free(cab);

    free(lst);
}

/*----------------------------------------------------------------------
 *  libereFilme
 *
 *  Recebe um ponteiro FLM para uma estrutura que representa um 
 *  filme e libera a area alocada.
 *
 */
void 
libereFilme(Filme *flm)
{
    if(flm == NULL) return;

    free(flm->nome);
    free(flm);
}

/*----------------------------------------------------------------------
 *  insiraFilme
 *
 *  Recebe um ponteito LST para uma estrutura que representa
 *  uma lista de filmes e um ponteiro FLM para uma estrutura
 *  que representa uma filme.
 *
 *  A funcao insere o filme na lista.
 *  
 */
void 
insiraFilme(ListaFilmes *lst, Filme *flm)
{
    Filme *cab;
    Filme *ultimo;

    if (lst == NULL || flm == NULL) {
        AVISO(insiraFilme: lista de filmes e/ou o filme vazio);
        return;
    } 

    cab = lst->cab;
    ultimo = cab->ant;

    flm->prox = cab; 
    flm->ant = ultimo;
    ultimo->prox = flm;
    cab->ant = flm;

    lst->nFilmes++;
}


/*---------------------------------------------------------------------
 *  contemFilme
 *
 *  Recebe um ponteito LST para uma estrutura que representa
 *  uma lista de filmes e um ponteiro FLM para uma estrutura
 *  que representa uma filme.
 *
 *  A funcao retorna  TRUE se o filme esta na lista e 
 *  FALSE em caso contrario. 
 *
 *  Consideramos que dois filmes f e g sao iguais se
 *
 *       - f->nome e' igual a g->nome 
 *       - f->nota e' igual a g->nota
 *       - f->ano  e' igual a g->ano 
 *
 *  Para comparar dois nomes voce pode usar alguma funcao da 
 *  bibliteca do c  como strcmp, strncmp (string,h) 
 *  ou a funcao strCmp (util.h).
 *
 */
Bool 
contemFilme(ListaFilmes *lst, Filme *flm)
{
    Filme *cab;
    Filme *atual;

    if (lst == NULL || flm == NULL) {
        AVISO(contemFilme: lista de filmes e/ou o filme vazio); 
        return FALSE;
    }

    cab = lst->cab;
    atual = cab->prox;

    while (atual != cab) {
        if (strCmp(atual->nome, flm->nome) == 0 && atual->nota == flm->nota && atual->ano == flm->ano) {
            return TRUE;
        } 

        atual = atual->prox;
    }

    return FALSE;
}

/*----------------------------------------------------------------------
 *  removaFilme
 *
 *  Remove da lista de filmes LST o filme apontado por FLM.
 *    
 *  Pre-condicao: a funcao supoe que o filme FLM esta 
 *                na lista LST.
 */
void 
removaFilme(ListaFilmes *lst, Filme *flm)
{
    if (lst == NULL || flm == NULL) {
        AVISO(removaFilme: lista de filmes e/ou o filme vazio);
        return;
    }

    flm->ant->prox = flm->prox;
    flm->prox->ant = flm->ant;

    libereFilme(flm);

    lst->nFilmes--;
}


/*----------------------------------------------------------------------
 *  mergeSortFilmes
 *
 *  Recebe uma lista de filmes LST e ordena a lista por nomes utilizando 
 *  o algoritmo mergeSort recursivo adaptado para listas encadeadas
 *  duplamente ligadas com cabeca.
 *
 *  ------------------------------------------------------------------
 *  OBSERVACAO IMPORTANTE:
 *
 *  A ordenacao deve ser feita 'in-place', ou seja o conteudo das
 *  celulas _nao deve_ ser copiado, apenas os ponteiros devem ser
 *  alterados.
 *
 *  A funcao so deve utilizar espaco extra O(1).  
 *
 *  Hmmm, ok, sem levar em consideracao o espaco O(lg n) utilizado
 *  pela pilha da recursao.  Em outras palavras, a funcao pode conter
 *  apenas declaracoes de umas poucas variaveis (um vetor v[0..n]
 *  conta como n variaveis e nao vale).
 * 
 *  ------------------------------------------------------------------
 *  DICA:
 * 
 *  Como a ordenação não será feita com vetores indexados, pense em
 *  uma maneira de chegar ao filme na posição floor(n/2) da lista.
 *
 *  ------------------------------------------------------------------
 *  Como a ordenação é por nome, veja a funcao strCmp em util.[h|c].
 */

static Filme *
merge(Filme *esq, int nEsq, Filme *dir, int nDir, Filme **ultimo)
{
    Filme cabeca;
    Filme *tail;
    int i, j;
    tail = &cabeca;
    i = 0;
    j = 0;

    while (i < nEsq && j < nDir) {
        if (strCmp(esq->nome, dir->nome) <= 0) {
            tail->prox = esq;
            esq->ant = tail;

            tail = esq;
            
            esq = esq->prox;
            i++;
        } else {
            tail->prox = dir;
            dir->ant = tail;

            tail = dir;
            dir = dir->prox;

            j++;
        }
    }
    
    while (i < nEsq) {
        tail->prox = esq;
        esq->ant = tail;

        tail = esq;
        esq = esq->prox;
        
        i++;
    }
    
    while (j < nDir) {
        tail->prox = dir;
        dir->ant = tail;

        tail = dir;
        dir = dir->prox;
        
        j++;
    }
    
    tail->prox = NULL;
    *ultimo = tail;
    
    cabeca.prox->ant = NULL;
    return cabeca.prox;
}

static Filme *
mergeSortR(Filme *inicio, int n, Filme **ultimo)
{
    int nEsq, nDir, i;
    Filme *meio;
    Filme *ultimoEsq, *ultimoDir;
    Filme *esq;
    Filme *dir;

    if (n == 1) {
        inicio->prox = NULL;
        inicio->ant = NULL;
        *ultimo = inicio;
        return inicio;
    }

    nEsq = n / 2;
    nDir = n - nEsq;

    meio = inicio;
    for (i = 0; i < nEsq; i++)
        meio = meio->prox;

    esq = mergeSortR(inicio, nEsq, &ultimoEsq);
    dir = mergeSortR(meio, nDir, &ultimoDir);

    return merge(esq, nEsq, dir, nDir, ultimo);
}

void 
mergeSortFilmes(ListaFilmes *lst)
{
    Filme *cab;
    Filme *ultimo;
    Filme *primeiro;

    if (lst == NULL || lst->cab == NULL || lst->nFilmes < 1) {
        AVISO(mergeSortFilmes: lista de filmes vazia ou invalida);
        return;
    }
    if (lst->nFilmes == 1){
        return;
    }

    cab = lst->cab;
    primeiro = mergeSortR(cab->prox, lst->nFilmes, &ultimo);

    cab->prox = primeiro;
    primeiro->ant = cab;
    ultimo->prox = cab;
    cab->ant = ultimo;
}

/*----------------------------------------------------------------------
 *  quickSortFilmes
 *
 *  Recebe uma lista de filmes LST e ordena a lista por nota utilizando
 *  o algoritmo quickSort adaptado para listas encadeadas duplamente
 *  ligadas com cabeca.
 *
 *  ------------------------------------------------------------------
 *  OBSERVACAO IMPORTANTE:
 *
 *  A ordenacao deve ser feita 'in-place', ou seja o conteudo das
 *  celulas _nao deve_ ser copiado, apenas os ponteiros devem ser
 *  alterados.
 *
 *  A funcao so deve utilizar espaco extra O(1).  
 *
 *  Hmmm, ok, sem levar em consideracao o espaco O(lg n) utilizado
 *  pela pilha da recursao.  Em outras palavras, a funcao pode conter
 *  apenas declaracoes de umas poucas variaveis (um vetor v[0..n]
 *  conta como n variaveis e nao vale).
 *
 */

static Filme *
getTail(Filme *node)
{
    while (node != NULL && node->prox != NULL){
        node = node->prox;
    }

    return node;
}

static Filme *
particione(Filme *inicio, Filme *fim, Filme **novoInicio, Filme **novoFim)
{
    Filme *pivo;
    Filme *atual;
    Filme *tail;
    Filme *prev;
    Filme *prox;
    Filme *temp;
    pivo = fim;
    atual = inicio;
    tail = pivo;
    prev = NULL;

    *novoInicio = NULL;

    while (atual != pivo) {
        prox = atual->prox;

        if (atual->nota < pivo->nota) {
            if (*novoInicio == NULL)
                *novoInicio = atual;

            prev = atual;
            atual = prox;
        } else {
            if (prev != NULL)
                prev->prox = prox;
            if (prox != NULL)
                prox->ant = prev;

            atual->prox = tail->prox;
            if (tail->prox != NULL)
                tail->prox->ant = atual;
            tail->prox = atual;
            atual->ant = tail;
            tail = atual;

            atual = prox;
        }
    }

    if (*novoInicio == NULL)
        *novoInicio = pivo;

    *novoFim = tail;

    temp = *novoInicio;
    temp->ant = NULL;
    while (temp->prox != NULL) {
        temp->prox->ant = temp;
        temp = temp->prox;
    }

    return pivo;
}

static Filme *
quickSortR(Filme *inicio, Filme *fim)
{
    Filme *novoInicio = NULL;
    Filme *novoFim = NULL;
    Filme *pivo;
    Filme *temp;

    if (inicio == NULL || inicio == fim)
        return inicio;

    pivo = particione(inicio, fim, &novoInicio, &novoFim);

    if (novoInicio != pivo) {
        temp = novoInicio;
        while (temp->prox != pivo)
            temp = temp->prox;
        temp->prox = NULL;

        novoInicio = quickSortR(novoInicio, temp);

        temp = getTail(novoInicio);
        temp->prox = pivo;
        pivo->ant = temp;
    }

    pivo->prox = quickSortR(pivo->prox, novoFim);
    if (pivo->prox != NULL)
        pivo->prox->ant = pivo;

    return novoInicio;
}

void 
quickSortFilmes(ListaFilmes *lst)
{
    Filme *cab;
    Filme *primeiro;
    Filme *ultimo;

    if (lst == NULL || lst->cab == NULL || lst->nFilmes < 1){
        AVISO(quickSortFilmes: lista de filmes vazia ou invalida);
        return;
    }
    if (lst->nFilmes == 1){
        return;
    }

    cab = lst->cab;
    primeiro = cab->prox;
    ultimo = cab->ant;

    primeiro->ant = NULL;
    ultimo->prox = NULL;

    primeiro = quickSortR(primeiro, ultimo);

    ultimo = getTail(primeiro);

    cab->prox = primeiro;
    primeiro->ant = cab;
    ultimo->prox = cab;
    cab->ant = ultimo;
}

/*----------------------------------------------------------------------
 *  hashFilmes [opcional]
 *
 *  Recebe uma lista de filmes LST e distribui as palavras que
 *  ocorrem nos nomes do filmes em uma tabela de dispersao 
 *  (hash table):
 *
 *     http://www.ime.usp.br/~pf/mac0122-2002/aulas/hashing.html
 *     http://www.ime.usp.br/~pf/mac0122-2003/aulas/symb-table.html
 *
 *  Antes de inserir uma palavra na tabela de dispersao todas a
 *  letras da palavra devem ser convertidas para minusculo. Com
 *  isto faremos que a busca de filmes que possuam uma dada
 *  palavra em seu nome nao seja 'case insensitive'. Para essa
 *  tarefa a funcao tolower() pode ser utilizada.
 *
 *  Esta funcao utiliza as funcoes freeST(), initST() e putFilmeST()
 *
 *  Para obter as palavras podemos escrever uma funcao peguePalavra()
 *  inspirada na funcao pegueNome do modulo lexer.c do EP3/EP4 ou
 *  ainda utilizar a funcao strtok() da biblioteca string.h:
 *  
 *      http://linux.die.net/man/3/strtok    (man page)
 *
 */
void
hashFilmes(ListaFilmes *lst)
{
    Filme *cab;
    Filme *atual;
    char *nome_copia;
    char *palavra;
    int len;
    
    if (lst == NULL) {
        AVISO(hashFilmes: lista de filmes vazia);
        return;
    }
    
    if (lst->cab == NULL) {
        AVISO(hashFilmes: cabeca da lista e NULL);
        return;
    }
    
    freeST();
    initST();
    
    cab = lst->cab;
    atual = cab->prox;
    
    while (atual != cab) {
        if (atual->nome == NULL) {
            atual = atual->prox;
            continue;
        }
        
        len = strlen(atual->nome) + 1;
        nome_copia = malloc(len * sizeof(char));
        if (nome_copia == NULL) {
            AVISO(hashFilmes: erro ao alocar memoria);
            return;
        }
        strcpy(nome_copia, atual->nome);
        
        palavra = strtok(nome_copia, " \t\n.,;:!?\"'()[]{}/-");
        while (palavra != NULL) {
            putFilmeST(palavra, atual);
            palavra = strtok(NULL, " \t\n.,;:!?\"'()[]{}/-");
        }
        
        free(nome_copia);
        atual = atual->prox;
    }
    
    AVISO(hashFilmes: tabela de dispersao (hash) criada);
}