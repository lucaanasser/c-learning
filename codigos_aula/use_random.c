# include <stdio.h>
# include "random.h"

int main() {
	int n = 10;
	int *v = malloc(n*sizeof(int));
	random_vec(v,n,30);
	print_vec(v,n);
return 0;
}
