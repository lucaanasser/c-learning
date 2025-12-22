# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define N 100

typedef struct {
	char** nome;
	int* idade;
	int len;
} Dicionario;

int busca(Dicionario* dic, char chave[]){
	for (int i = 0; i < dic->len; i++) {
		if (strcmp((dic->nome)[i], chave) == 0) return (dic->idade)[i];
	}
	return -1;
}

void adiciona(Dicionario* dic, char chave[], int idade){
	int pos = dic->len;
	(dic->nome)[pos] = chave;
	(dic->idade)[pos] = idade;
	(dic->len)++;
}

void main() {

	char** nomes = malloc(N*sizeof(char*));
	int* idades = malloc(N*sizeof(int));
	Dicionario D;
	D.nome = nomes;
	D.idade = idades;
	D.len = 0;
	
	adiciona(&D,"Fábio",26);
	adiciona(&D,"Vitor",20);
	adiciona(&D,"Igor",12);
	
	printf("Igor tem %d anos\n",busca(&D,"Igor"));

/*	
	char* nome_aux = malloc(100*sizeof(char));
	char* meunome = malloc(100*sizeof(char));
	strcpy(meunome, "Fábio");
	printf("%s\n",meunome);
*/
}











