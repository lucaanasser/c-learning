void selection_sort(int *A, int lenght) {
  int min;
  int aux;
  
  if(lenght <= 1) {
    return;
  }
  for(int i = 0; i < lenght; i++) {
    min = i;
    for(int j = i + 1; j < lenght; j++){
      if(A[min] > A[j]) {
        min = j;
      }
    }
    if( min != i) {
      aux = A[i];
      A[i] = A[min];
      A[min] = aux;
    }
  }
}

void recursive_selection_sort(int *A, int lenght) {
  if(lenght <= 1) {
    return;
  }

  selection_sort_aux(A, lenght, 0);
}

void selection_sort_aux(int *A, int lenght, int start) {
  if(start >= lenght - 1) {
    return;
  }
  
  int min = find_min_index(A, lenght, start);
  
  if(min != start) {
    int aux = A[start];
    A[start] = A[min];
    A[min] = aux;
  }
  
  selection_sort_aux(A, lenght, start + 1);
}

int find_min_index(int *A, int lenght, int start) {
    if(start == lenght - 1) {
      return start;
    }
    
    int min = find_min_index(A, lenght, start + 1);
    
    if(A[min] > A[start]) {
      return start;  
    } else {
      return min;  
    }
}