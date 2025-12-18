/* 
 * IMPLEMENTACAO de funcoes de uso geral 
 *
 */

/* interface para este modulo */
#include "util.h" 

#include <stdio.h>     /* fgets(), printf() */
#include <stdlib.h>    /* malloc(), NULL, EXIT_FAILURE */
#include <string.h>    /* strlen() */
#include <ctype.h>     /* tolower() */

/* tamanho maximo de um string neste programa como nome de arquivo 
   ou nome um filme */
#define TAM_STR 256

#define DEBUG


/*----------------------------------------------------------------------
 * achePalavra
 *
 * Recebe o string PAL com tamanho TPAL, e outro string TEXTO com
 * tamanho TTEX e retornar TRUE caso a PAL ocorra em TEXTO, e
 * FALSE em caso contrário. 
 * 
 * A busca nao deve levar em consideracao se as letras em PAL ou
 * TEXTO sao em caixa alta (maiusculas) ou caixa normal
 * (minusculas). Assim, a busca deve ser 'case insensitive'.
 * 
 * Dica: use algum algoritmo visto em sala.
 *
 */
Bool
achePalavra(unsigned char *pal, int tPal, unsigned char *texto, int tTex)
{
    if (pal == NULL || texto == NULL || tPal <= 0 || tTex <= 0) {
        AVISO(achePalavra: os parametros usados estaao vazios ou invalidos);
        return FALSE;
    }

    int CharErrado[256];

    for (int i = 0; i < 256; i++) {
        CharErrado[i] = tPal;
    }

    for (int i = 0; i < tPal - 1; i++) {
        CharErrado [tolower(pal[i])] = tPal - 1 - i;
    }

    int i = 0;
    while (i <= tTex - tPal) {
        int j = tPal - 1;
        while (j >= 0 && tolower(texto[i + j]) == tolower(pal[j])) {
            j--;
        }

        if (j < 0) {
            return TRUE;
        }

        i += CharErrado[tolower(texto[i + j])];
    }
    
    return FALSE;  
}

/*----------------------------------------------------------------------
 *   strCmp(const char *s1, const char *s2)
 *
 *   Comportamento identico ao da funcao strcmp da interface string.h
 *   da libC. A unica diferenca e que esta funcao desconsidera se as
 *   letras sao maiusculas ou mininusculas.
 *
 *   copiado da  gLibc
 *
 *   Ver http://fossies.org/dox/glibc-2.20/string_2strcmp_8c_source.html
 *   ou a copia nas notas de aula de MAC0121.
 *     
 *   ------------------------------------------------------------------
 *   NAME
 *      strcmp - compare two strings
 *
 *   SYNOPSIS
 *      #include <string.h>
 *
 *      int strcmp(const char *s1, const char *s2);
 *
 *   DESCRIPTION
 *      The  strcmp() function compares the two strings s1 and s2.  
 *      It returns an integer less than, equal to, or greater than
 *      zero if s1 is found, respectively, to be less than, to match, 
 *      or be greater than s2.
 *
 */

int  
strCmp(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;
    unsigned char c1, c2;
 
    do
    {
        c1 = tolower((unsigned char) *p1++); /* tolower foi acrescentado */ 
        c2 = tolower((unsigned char) *p2++); /* tolower foi acrescentado */
        if (c1 == '\0')
            return c1 - c2;
    }
    while (c1 == c2);
 
    return c1 - c2;
}


/*--------------------------------------------------------------
 *   leiaString
 *
 *   RECEBE como parametros um string STR e um inteiro SIZE e LE
 *   da entrada padrao no maximo SIZE-1 caracteres e ARMAZENA em
 *   STR. A leitura para depois de um ENTER e o ENTER _nao_ e
 *   incluido no string STR.  A funcao retorna o numero de
 *   caracteres no string.
 *
 *   Pre-condicao: SIZE <= TAM_STR
 *
 *   . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 *   > man fgets
 *   char *fgets(char *s, int size, FILE *stream);
 *
 *   fgets() reads in at most one less than size characters from
 *   stream and stores them into the buffer pointed to by s.
 *   Reading stops after an EOF or a newline.  If a newline is
 *   read, it is stored into the buffer.  A terminating null byte
 *   ('\0') is stored after the last character in the buffer.
 */

int 
leiaString(char str[], int size)
{
    int len;
    char s[TAM_STR];

    /* remove qualquer newline que estava no buffer */
    scanf(" ");

    /* leitura do string: ler info sobre fgets() */
    fgets(s, TAM_STR, stdin);

    /* sobreescreve  um possivel newline do final com '\0' */
    len = strlen(s); 
    if (s[len-1] == ENTER) 
    {
        len--;
        s[len] = '\0';
    }

    if (len > size)
    {
        s[size-1] = '\0';
        len = size-1;
    }
    strncpy(str, s, size);

#ifdef DEBUG
    printf("AVISO: leiaString: string lido '%s' tem %d caracteres\n", s, len);
#endif
    return len;
}

