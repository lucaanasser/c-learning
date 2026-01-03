#include <stdio.h>  /* printf(), scanf() */ 

#include "main.h"

#include "filmes.h"   /* crieListaFilmes(), crieFilme(), 
                         inseraFilme(),  mergeSortFilmes() */
#include "iofilmes.h" /* carregueListaFilmes(), graveListaFilmes(), 
                         mostreFilme(), mostreListaFilmes() */
#include "util.h"     /* mallocSafe(), leiaString() */
#include "st.h"       /* initST(), putFilmeST(), getFilmeST(), showST(),
                         freeST() */

/*------------------------------------------------------------------- 
  P R O T O T I P O S 
*/

/* A funcao leiaOpcao so e usada neste arquivo. */
static char  leiaOpcao(); 


/*------------------------------------------------------------------- 
  M A I N 
*/
int 
main(int argc, char *argv[])
{
    ListaFilmes *lst = crieListaFilmes(); 
    char         opcao;
    /* declaracao das demais variaveis do main */

    initST();
    
    /*-----------------------------------------------------*/
    /* iterara ate o usuario digitar 'x' para sair         */
    do 
    { 

        opcao = leiaOpcao();


        switch (opcao) 
        {
            /*---------------------------------------------*/
        case CARREGAR_SER:
        {
            carregueListaFilmes(lst,FALSE);
            break;
        }  

        /*---------------------------------------------*/
        case CARREGAR_ER:
        {
            carregueListaFilmes(lst,TRUE);
            break;
        }  

        /*---------------------------------------------*/
        case PROCURAR:
        {
            char nome[TAM_STR];
            Filme *cab;
            Filme *atual;
            Bool encontrado;

            printf("Digite o nome do filme: ");
            leiaString(nome, TAM_STR);

            cab = lst->cab;
            atual = cab->prox;
            encontrado = FALSE;

            while (atual != cab) {
                if (strCmp(atual->nome, nome) == 0) {
                    mostreFilme(atual);
                    encontrado = TRUE;
                }
                atual = atual->prox;
            }

            if (!encontrado) {
                printf("Filme '%s' nao encontrado.\n", nome);
            }
            break;
        }

        /*---------------------------------------------*/
        case HASH: /* opcional */
        {
            hashFilmes(lst);
            break;
        }

        /*---------------------------------------------*/
        case PROCURAR_HASH: /* opcional */
        {
            char palavra[TAM_STR];
            char resposta;
            ListaPtrFilmes *listaPtr;
            ListaPtrFilmes *atual;

            listaPtr = getFilmeST("");
            if (listaPtr == NULL) {
                break;
            }

            printf("Digite um parte do nome do filme a ser procurado: ");
            leiaString(palavra, TAM_STR);

            listaPtr = getFilmeST(palavra);

            atual = listaPtr;
            while (atual != NULL) {
                mostreFilme(atual->ptrFlm);
                printf(" Esse eh o filme procurado? [s/n/x] (x para sair): ");
                scanf(" %c", &resposta);
                
                if (resposta == 's' || resposta == 'S' || resposta == 'x' || resposta == 'X') {
                    break;
                }
                
                atual = atual->proxPtr;
            }
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR_HASH: /* opcional */
        {
            showST();
            break;
        }

        /*---------------------------------------------*/
        case LIMPAR_HASH: /* opcional */
        {
            freeST();
            initST();
            printf("Tabela de simbolos limpa.\n");
            break;
        }

        /*---------------------------------------------*/
        case INSERIR:
        {
            Filme       *flm = NULL;      

            char  dist[TAM_DIST+1];  
            int   votos;             
            float nota;              
            char  nome[TAM_STR+1];   
            int   ano;               

            printf("Digite o nome do filme: ");
            leiaString(nome, TAM_STR);

            printf("Digite o ano: ");
            scanf("%d", &ano);

            printf("Digite a nota: ");
            scanf("%f", &nota);

            printf("Digite o numero de votos: "); 
            scanf("%d", &votos);

            printf("Digite a distribuicao: ");
            leiaString(dist, TAM_DIST+1);
   
            flm = crieFilme(dist, votos, nota, nome, ano);
            mostreFilme(flm);
            
            insiraFilme(lst, flm);
            printf("Filme inserido com sucesso.\n");

            break;
        }

        /*---------------------------------------------*/
        case REMOVER:
        {
            char nome[TAM_STR];
            Filme *cab;
            Filme *atual;
            Bool encontrado;

            printf("Digite o nome do filme: ");
            leiaString(nome, TAM_STR);

            cab = lst->cab;
            atual = cab->prox;
            encontrado = FALSE;

            while (atual != cab) {
                if (strCmp(atual->nome, nome) == 0) {
                    removaFilme(lst, atual);
                    printf("Filme '%s' removido.\n", nome);
                    encontrado = TRUE;
                    break;
                }
                atual = atual->prox;
            }

            if (!encontrado) {
                printf("Filme '%s' nao encontrado.\n", nome);
            }
            break;
        }

        /*---------------------------------------------*/
        case ORDENAR_NOME_M:
        {
            if (lst == NULL || lst->cab == NULL || lst->nFilmes < 1) {
                printf("AVISO: mergeSortFilmes: lista de filmes vazia ou invalida\n");
            } else {
                mergeSortFilmes(lst);
                printf("Lista ordenada por nome (mergeSort).\n");
            }
            break;
        }

        /*---------------------------------------------*/
        case ORDENAR_NOTA_Q: 
        {
            if (lst == NULL || lst->cab == NULL || lst->nFilmes < 1) {
                printf("AVISO: quickSortFilmes: lista de filmes vazia ou invalida\n");
            } else {
                quickSortFilmes(lst);
                printf("Lista ordenada por nota (quickSort).\n");
            }
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR:
        {
            mostreListaFilmes(lst);
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR_MENOR:
        {
            mostrePioresFilmes(lst);
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR_MAIOR:
        {
            mostreMelhoresFilmes(lst);
            break;
        }
      
        /*---------------------------------------------*/
        case LIMPAR:
        {
            libereListaFilmes(lst);
            lst = crieListaFilmes();
            printf("Lista de filmes limpa.\n");
            break;
        }

        /*---------------------------------------------*/
        case SAIR:
        {
            break;
        }

        default :
        {
            printf("main: opcao '%c' nao reconhecida\n", opcao);
            break;
        }
        
        } /* switch */
    } 
    while (opcao != SAIR);

    libereListaFilmes(lst); 
    freeST(); 

    return 0;
}


/*---------------------------------------------------------------------
  leiaOpcao()
   
  Le e retorna o caractere correspondente a opcao do usuario.
*/

char 
leiaOpcao()
{
    char opcao;
    char listaOpcoes1[] = 
        "\n================================================"
        "======================\n"
        "  (c) carregar um arquivo de dados sem eliminar repeticoes\n"
        "  (C) carregar um arquivo de dados eliminando repeticoes\n"
        "  (p) procurar a nota de um filme\n"
        "  (h) criar    a  TS com as palavras em nomes de filmes (opcional)\n"
        "  (P) procurar na TS a nota de um filme (opcional)\n"
        "  (M) mostrar  a  TS (opcional)\n"
        "  (L) limpar   a  TS (opcional)\n"
        "  (i) inserir  um filme\n"
        "  (r) remover  um filme\n";
    char listaOpcoes2[] = 
        "  (o) ordenar  a lista de filmes por nome (mergeSort)\n"
        "  (q) ordenar  a lista de filmes por nota (quickSort)\n"
        "  (m) mostrar  todos os filmes\n"
        "  (<) mostrar  N filmes com nota _menor_ que X e pelo menos V votos\n"
        "  (>) mostrar  N filmes com nota _maior_ que X e pelo menos V votos\n"
        "  (l) limpar   a lista de filmes\n"
        "  (x) sair     do programa\n\n";

    printf("%s",listaOpcoes1);
    printf("%s",listaOpcoes2);
    printf("Digite uma opcao: ");
    scanf(" %c", &opcao);

    return opcao;
}


