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
            break;
        }

        /*---------------------------------------------*/
        case HASH: /* opcional */
        {
            break;
        }

        /*---------------------------------------------*/
        case PROCURAR_HASH: /* opcional */
        {
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR_HASH: /* opcional */
        {
            break;
        }

        /*---------------------------------------------*/
        case LIMPAR_HASH: /* opcional */
        {
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
            
            /* COMPLETAR ESSA OPERAÇÃO */

            break;
        }

        /*---------------------------------------------*/
        case REMOVER:
        {
            break;
        }

        /*---------------------------------------------*/
        case ORDENAR_NOME_M:
        {
            break;
        }

        /*---------------------------------------------*/
        case ORDENAR_NOTA_Q: 
        {
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR:
        {
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR_MENOR:
        {
            break;
        }

        /*---------------------------------------------*/
        case MOSTRAR_MAIOR:
        {
            break;
        }
      
        /*---------------------------------------------*/
        case LIMPAR:
        {
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


