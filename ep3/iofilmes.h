/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  Aqui estao os prototipo das funcoes de entrada e saida 
  de filmes.
  
*/

#ifndef _IOFILMES_H
#define _IOFILMES_H

#include "util.h"   /* Bool */
#include "filmes.h" /* ListaFilmes, Filme */

void
carregueListaFilmes(ListaFilmes *lst, Bool semRepeticoes);

void
mostreFilme(Filme *flm);

void
mostreListaFilmes(ListaFilmes *lst);

void
mostrePioresFilmes(ListaFilmes *lst);

void
mostreMelhoresFilmes(ListaFilmes *lst);

#endif
