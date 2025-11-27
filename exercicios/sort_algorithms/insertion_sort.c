void insertion_sort(int *A, int lenght) {
  int pivot_1 = 1;
  int pivot_2 = 1;
  int aux = 0;

  while(pivot_1 < lenght) {
    if(A[pivot_1] > A[pivot_1 - 1]) {
      pivot_1++; 
    } else {
      aux = A[pivot_1];
      A[pivot_1] =   A[pivot_1 - 1];
      A[pivot_1 - 1] = aux;
      pivot_2 = pivot_1 - 1;
      while(pivot_2 > 0) {
        if(A[pivot_2] > A[pivot_2 - 1]) {
          pivot_2 = 0; 
        } else {
          aux = A[pivot_2];
          A[pivot_2] = A[pivot_2 - 1];
          A[pivot_2 - 1] = aux;
          pivot_2--;
        }
      }
      pivot_1++;
    }  
  }
}

recursive_insertion_sort(int *A, int lenght) {
  int aux = 0;
  if(lenght <= 1) return;
  
  recursive_insertion_sort(A, lenght - 1);
  
  if(A[lenght - 1] > A [lenght - 2]) {
    return;
  } else {
      aux = A[lenght - 1];
      A[lenght - 1] = A[lenght - 2];
      A[lenght - 2] = aux;
  
      insert(A, lenght - 2);
  } 
}

insert(int *A, int pos) {
  int aux = 0;
  if(pos <= 0) return;
  
  if(A[pos] > A[pos - 1]) {
    return;
  } 
  else {
    aux = A[pos];
    A[pos] = A[pos - 1];
    A[pos - 1] = aux;
    
    insert(A, pos - 1);
  }
}