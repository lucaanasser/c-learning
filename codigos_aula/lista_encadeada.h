struct cel {
	int		conteudo;
	struct cel *seg;
};

typedef struct cel celula;

celula*  adicionar_LE(celula *LE, int x) {
	celula *nova_celula;
	nova_celula = malloc(sizeof(celula));
	nova_celula->conteudo = x;
	nova_celula->seg = LE;
	return nova_celula;
}

celula* cria_LE(int v[], int n) {
	celula *LE;
	LE = malloc(sizeof(celula));
	LE->conteudo = v[0];
	LE->seg = NULL;
	for (int i = 1; i < n; i++) {
		LE = adicionar_LE(LE,v[i]);
	}
	return LE;
}

void imprime_LE(celula *LE) {
	celula *p;
	for (p = LE;p != NULL; p = p-> seg) {
		printf("%d, ",p->conteudo);
	}
	printf("\b\b \n");
}

void adicionar_LE_CC(celula *LE, int x) {
	celula *nova_celula;
	nova_celula = malloc(sizeof(celula));
	nova_celula->conteudo = x;
	
	nova_celula->seg = LE->seg;
	LE->seg = nova_celula;
}

celula* cria_LE_CC(int v[], int n) {
	celula *LE;
	LE = malloc(sizeof(celula));
	LE->seg = NULL;
	for (int i = n-1; i >=0; i--) {
		adicionar_LE_CC(LE,v[i]);
	}
	return LE;
}

void imprime_LE_CC(celula *LE) {
	celula *p;
	for (p = LE->seg;p != NULL; p = p-> seg) {
		printf("%d\n",p->conteudo);
	}
}

/*
Esta função recebe um inteiro x e uma lista encadeada lst com cabeça.
Devolve o endereço de uma célula que contém x,
ou devolve NULL se tal célula não existe
*/
celula *Busca_LE_CC (int x, celula *lst) {
	celula *p;
	p = lst->seg;
	while (p != NULL && p->conteudo != x) 
		p = p->seg;
	return p;
}

celula *Busca_LE_CC_R (int x, celula *lst) {
	if (lst->seg == NULL) 
		return NULL;
	if (lst->seg->conteudo == x) 
		return lst->seg;
	return Busca_LE_CC_R(x,lst->seg);
}

/*
Esta função recebe o endereço p de uma celula em uma lista encadeada e remove da lista a celula p->seg
A função fuspõe que p!=NULL e p->seg != NULL
*/
void Remove_LE(celula *p) {
	celula *lixo;
	lixo = p->seg;
	p->seg = lixo->seg;
	free(lixo);
}

void Insere_LE(int y, celula *p) {
	celula *nova;
	nova = malloc(sizeof(celula));
	nova->conteudo = y;
	nova->seg = p->seg;
	p->seg = nova;
}

/*
Esta função recebe uma lista encadeada lst com cabeça
e remove da lista a primeira celula que contiver x
se tal celula existir
*/
void BuscaERemove_LE(int x, celula *lst) {
	celula *p,*q;
	p = lst;
	q = lst->seg;
	while (q != NULL && q->conteudo != x) {
		p = q;
		q = q->seg;
	}
	if (q != NULL) {
		p->seg = q->seg;
		free(q);
	}
}
