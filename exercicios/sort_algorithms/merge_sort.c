void merge_sort(int *A, int lenght) {
  if(lenght <= 1) {
    return;
  }
  
  merge_sort_aux(A, 0, lenght - 1);
}

void merge_sort_aux(int *A, int start, int end) {
  if(start >= end){
    return;
  }
  int middle = (start + end) / 2;
  
  merge_sort_aux(A, start, middle);
  merge_sort_aux(A, middle + 1, end);
  
  merge(A, start, middle, end);
}

void merge(int *A, int start, int middle, int end) {
  int temp[end - start + 1];
  
  int i = start;  
  int j = middle + 1;  
  int k = 0;    // preenche o array temp
  
  // Loop principal: enquanto tem elementos nas duas metades
  while (i <= middle && j <= end) {
    if (A[i] <= A[j]) {
      temp[k] = A[i];
      i++;
    } else {
      temp[k] = A[j];
      j++;
    }
    k++;
  }
  
  while(i <= middle) {
    temp[k] = A[i];
    k++;
    i++;
  }
  
  while(j <= end) {
    temp[k] = A[j];
    k++;
    j++;
  }
  
  
  for(int i = start, k = 0; i <= end; i++, k++) {
    A[i] = temp[k];
  }
}



