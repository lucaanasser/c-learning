int fibonacci(int n) {
	if(n == 0) return 0;
	if(n == 1) return 1;

	int f = fibonacci(n - 1) + fibonacci(n - 2);

	return f; 
}


int fibonacci_top_down(int n) {
	int *memo = calloc(n + 1, sizeof(int));

	int f = fibonacci_top_down_aux(n, memo);

	free(memo);
	return f;
}

int fibonacci_top_down_aux(int n, int *memo) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	

	if(memo[n] == 0){
		int f = fibonacci_top_down_aux(n - 1, memo) + fibonacci_top_down_aux(n - 2, memo);
		memo[n] = f;	
	}

	return memo[n]; 
}


int fibonacci_bottom_up(int n) {
	int table[n + 1];
	table[0] = 0;
	table[1] = 1;

	if(n == 0) return table[0];
	if(n == 1) return table[1];
	
	int i = 2;

	while(i <= n) {
		table[i] = table[i - 1] + table[i - 2];
		i++;
	}

	return table[n];
}

int fibonacci_bottom_up_optiomization(int n) {
	int table[3];
	table[0] = 0;
	table[1] = 1;

	if(n == 0) return table[0];
	if(n == 1) return table[1];
	
	int i = 2;

	while(i <= n) {
		table[2] = table[1] + table[0];
		table[0] = table[1];
		table[1] = table[2];

		i++;
	}

	return table[2];
}

