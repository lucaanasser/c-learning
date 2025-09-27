# include <stdio.h>

typedef struct Complex Complexo;

struct Complex {
	int real;
	int img;
};

void print_complex(struct Complex x) {
	printf("O meu número complexo é %d + %d i\n", x.real, x.img);
}

struct Complex soma_complexos(struct Complex x, struct Complex y) {
	struct Complex z;
	z.real = x.real + y.real;
	z.img = x.img + y.img;
	return z;
}

void main() {
	struct Complex meu_complexo;
	meu_complexo.real = 3;
	meu_complexo.img = 12;
	
	struct Complex y = {20,8};
	
	struct Complex z = soma_complexos(meu_complexo, y);
	
	print_complex(z);
}
