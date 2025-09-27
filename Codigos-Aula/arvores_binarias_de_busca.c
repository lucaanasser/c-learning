# include <stdio.h>
# include <stdlib.h>

typedef struct Node Node;

struct Node {
	int key;
	Node *left, *right,*daddy;
	//struct Node* right;
	//struct Node* daddy;
};

typedef struct Tree{
	Node* root;
} Tree;

void inorder_tree_walk(Node* x) {
	if (x != NULL) {
		inorder_tree_walk(x->left);
		printf(" %d ", x->key);
		inorder_tree_walk(x->right);
	} 
}

void preorder_tree_walk(Node* x) {
	if (x != NULL) {
		printf(" %d ", x->key);
		preorder_tree_walk(x->left);
		preorder_tree_walk(x->right);
	} 
}

void posorder_tree_walk(Node* x) {
	if (x != NULL) {
		posorder_tree_walk(x->left);
		posorder_tree_walk(x->right);
		printf(" %d ", x->key);
	} 
}

Node* tree_search(Node* x, int k) {
	if ((x == NULL) || (k == x->key)) 
		return x;
	if (k < x->key)
		return tree_search(x->left,k);
	return tree_search(x->right,k); 
}

Node* iterative_tree_search(Node* x, int k) {
	while ((x != NULL) && (k != x->key)) {
		if (k < x->key) 
			x = x->left;
		else 
			x = x->right;
	}
	return x;
}

int tree_minimum(Node* x) {
	while (x->left != NULL)
		x = x->left;
	return x->key;
}

int tree_maximum(Node* x) {
	while (x->right != NULL)
		x = x->right;
	return x->key;
}

Node* tree_minimum_node(Node* x) {
	while (x->left != NULL)
		x = x->left;
	return x;
}

Node* tree_maximum_node(Node* x) {
	while (x->right != NULL)
		x = x->right;
	return x;
}

Node* tree_successor(Node* x) {
	if (x->right != NULL)
		return tree_minimum_node(x->right);
	
	Node* y = x->daddy;
	while ((y != NULL) && (x == y->right)) {
		x = y;
		y = x->daddy;
	}
	return y;
}

void tree_insert(Tree* T, Node* z) {
	Node* y = NULL; //invariante: y é sempre o pai de x
	Node* x = T->root;
	while (x != NULL) {
		y = x;
		if (z->key < x->key) 
			x = x->left;
		else
			x = x->right;
	}
	z->daddy = y;
	
	if (y == NULL) // y é NULL se e somente se a árvore está vazia
		T->root = z;
	else {
		if (z->key < y->key)
			y->left = z;
		else 
			y->right = z;
	}
	
}

void tree_delete(Tree* T, Node *z) {
	Node* y;
	if ((z->left == NULL) || (z->right == NULL))
		y = z;
	else y = tree_successor(z);
	
	Node* x;
	if (y->left != NULL)
		x = y->left;
	else x = y->right;
	
	if (x != NULL)
		x->daddy = y->daddy;
	
	if (y->daddy == NULL)
		T->root = NULL;
	else {
		if (y == y->daddy->left) 
			y->daddy->left = x;
		else y->daddy->right = x;
	}
	
	if (y != z) {
		z->key = y->key;
		free(y);
		}
}

void main() {

	Node* N2 = malloc(sizeof(Node));
	Node* N3 = malloc(sizeof(Node));
	Node* N5 = malloc(sizeof(Node));
	Node* N7 = malloc(sizeof(Node));
	Node* N11 = malloc(sizeof(Node));

/*	
	N2->key = 2; 
	N2->left = NULL; 
	N2->right = N3; 
	N2->daddy = N5;
	
	N3->key = 3; 
	N3->left = NULL; 
	N3->right = NULL; 
	N3->daddy = N2;
	
	N5->key = 5; 
	N5->left = N2; 
	N5->right = N11; 
	N5->daddy = NULL;
	
	N7->key = 7; 
	N7->left = NULL; 
	N7->right = NULL; 
	N7->daddy = N11;
	
	N11->key = 11; 
	N11->left = N7; 
	N11->right = NULL; 
	N11->daddy = N5;
*/

	N2->key = 2;
	N3->key = 3;
	N5->key = 5;
	N7->key = 7;
	N11->key = 11;
	 	
	 	
	Node* N4 = malloc(sizeof(Node));
	N4->key = 4;
	 	
	Tree* T = malloc(sizeof(Tree));
	tree_insert(T,N3);
	tree_insert(T,N11);
	tree_insert(T,N2);
	tree_insert(T,N4);
	tree_insert(T,N7);
	tree_insert(T,N5);
	
	printf("Inorder: ");
	inorder_tree_walk(T->root);
	printf("\n");
	printf("Preorder: ");
	preorder_tree_walk(T->root);
	printf("\n");
	printf("Posorder: ");
	posorder_tree_walk(T->root);
	printf("\n");
	
	Node* NN = tree_search(T->root,3);
	tree_delete(T,NN);
	
	printf("Preorder: ");
	preorder_tree_walk(T->root);
	printf("\n");


//	int d = 3;
//	Node* y = iterative_tree_search(N5,d);
//	printf("A chave do nó encontrado é %d\n",y->key);
	
//	Node* S = tree_successor(y);
//	printf("O sucessor de %d é %d\n",y->key,S->key);
	
	Node* N = tree_minimum_node(T->root);
	Node* S = tree_successor(N);
	while (S != NULL) {
		printf("O sucessor de %d é %d\n",N->key,S->key);
		N = S;
		S = tree_successor(N);
		}
		
	
//	printf("O mínimo da árvore é %d\n",tree_minimum(N5));
//		printf("O máximo da árvore é %d\n",tree_maximum(N5));
}
