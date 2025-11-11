# include <stdio.h>
# include <string.h>

void print_function_matrix(int lin, int col, int M[lin][col], int (*f)(int)) {
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d\t",(*f)(M[i][j]));
		}
		printf("\n");
	}
}

int quadrado(int x) {
	return x*x;
}

int id(int x) {
	return x;
}

void main() {

int lin = 3;
int col = 5;

int minha_matriz[lin][col];

for (int i = 0; i < lin; i++) {
	for (int j = 0; j < col; j++) {
		minha_matriz[i][j] = i*j;
	}
}

print_function_matrix(lin,col,minha_matriz,id);
printf("\n\n");
print_function_matrix(lin,col,minha_matriz,quadrado);
/*
char nome[10][10];
int idade[10];

int index = 0;
strcpy(nome[index],"Fábio");
idade[index] = 26;
index++;

strcpy(nome[index],"Mota");
idade[index] = 50;
index++;


for (int i = 0; i < index; i++) {
	printf("A idade de %s é %d\n",nome[i],idade[i]);
}
*/
}
