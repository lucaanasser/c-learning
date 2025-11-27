void quick_sort(int *A, int length) {
    if (length <= 1) return;

    quick_sort_aux(A, 0, length - 1);
}

void quick_sort_aux(int *A, int start, int end) {
    if (start >= end) return;

    int p = partition(A, start, end);
    quick_sort_aux(A, start, p - 1);
    quick_sort_aux(A, p + 1, end);
}

int partition(int *A, int start, int end) {
    int pivot = A[end];
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (A[j] < pivot) {
            i++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }

    i++; 
    int tmp = A[i];
    A[i] = A[end];
    A[end] = tmp;

    return i;
}
