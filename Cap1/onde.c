int onde (int x, int v[], int n){
	int j = 0;
	while (j < n && v[j] != x){
		j++;
	}
	return j;
}