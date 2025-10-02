#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Sorting Algorithms 

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

//Merge using heap buffers (safer than VLAs for large n)
static void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc((size_t)n1 * sizeof(int));
    int *R = (int *)malloc((size_t)n2 * sizeof(int));
    if (!L || !R) {
        // Allocation failed; clean up and return to avoid UB 
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++]; else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

static int partition(int arr[], int low, int high) {
    int pivot = arr[high];          //Lomuto partition with last element as pivot
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        }
    }
    int t = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = t;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); //returns pivot final index for Lomuto 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helpers 
void copyArray(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

//Main
int main(void) {
    int n;
    printf("Enter the size of the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid size\n");
        return 1;
    }

    int *original = (int *)malloc((size_t)n * sizeof(int));
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (!original || !arr) {
        fprintf(stderr, "Memory allocation failed\n");
        free(original);
        free(arr);
        return 1;
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) original[i] = (rand() % 999) + 1; 

    clock_t start, end;
    double total_time, avg_time;
    int runs = 1000;

    // Bubble Sort 
    start = clock();
    for (int k = 0; k < runs; k++) {
        copyArray(original, arr, n);
        bubbleSort(arr, n);
    }
    end = clock();
    total_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time = total_time / runs;
    printf("\nBubble Sort: Total Time = %f sec, Average Time = %f sec\n", total_time, avg_time);

    // Insertion Sort 
    start = clock();
    for (int k = 0; k < runs; k++) {
        copyArray(original, arr, n);
        insertionSort(arr, n);
    }
    end = clock();
    total_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time = total_time / runs;
    printf("Insertion Sort: Total Time = %f sec, Average Time = %f sec\n", total_time, avg_time);

    // Selection Sort 
    start = clock();
    for (int k = 0; k < runs; k++) {
        copyArray(original, arr, n);
        selectionSort(arr, n);
    }
    end = clock();
    total_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time = total_time / runs;
    printf("Selection Sort: Total Time = %f sec, Average Time = %f sec\n", total_time, avg_time);

    // Merge Sort 
    start = clock();
    for (int k = 0; k < runs; k++) {
        copyArray(original, arr, n);
        mergeSort(arr, 0, n - 1);
    }
    end = clock();
    total_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time = total_time / runs;
    printf("Merge Sort: Total Time = %f sec, Average Time = %f sec\n", total_time, avg_time);

    // Quick Sort 
    start = clock();
    for (int k = 0; k < runs; k++) {
        copyArray(original, arr, n);
        quickSort(arr, 0, n - 1);
    }
    end = clock();
    total_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time = total_time / runs;
    printf("Quick Sort: Total Time = %f sec, Average Time = %f sec\n", total_time, avg_time);

    free(original);
    free(arr);
    return 0;
}
