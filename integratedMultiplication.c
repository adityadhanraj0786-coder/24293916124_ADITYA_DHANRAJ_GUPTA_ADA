#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------- Iterative Multiplication ----------------
void multiplyIterative(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// ---------------- Divide and Conquer ----------------
int* alloc_matrix(int n) {
    int* m = (int*)malloc(sizeof(int) * n * n);
    if (!m) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return m;
}
void free_matrix(int* m) { free(m); }

void zero_block(int* M, int n, int stride) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i * stride + j] = 0;
}
void add_into(int* dest, int* src, int n, int dest_stride, int src_stride) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i * dest_stride + j] += src[i * src_stride + j];
}

void recursive_multiply(int* A, int* B, int* C, int n, int strideA, int strideB, int strideC) {
    if (n == 1) {
        C[0] += A[0] * B[0];
        return;
    }

    int k = n / 2;
    int *A11 = A, *A12 = A + k, *A21 = A + k * strideA, *A22 = A21 + k;
    int *B11 = B, *B12 = B + k, *B21 = B + k * strideB, *B22 = B21 + k;
    int *C11 = C, *C12 = C + k, *C21 = C + k * strideC, *C22 = C21 + k;

    zero_block(C11, k, strideC);
    zero_block(C12, k, strideC);
    zero_block(C21, k, strideC);
    zero_block(C22, k, strideC);

    int* T = alloc_matrix(k);

    recursive_multiply(A11, B11, C11, k, strideA, strideB, strideC);
    zero_block(T, k, k);
    recursive_multiply(A12, B21, T, k, strideA, strideB, k);
    add_into(C11, T, k, strideC, k);

    recursive_multiply(A11, B12, C12, k, strideA, strideB, strideC);
    zero_block(T, k, k);
    recursive_multiply(A12, B22, T, k, strideA, strideB, k);
    add_into(C12, T, k, strideC, k);

    recursive_multiply(A21, B11, C21, k, strideA, strideB, strideC);
    zero_block(T, k, k);
    recursive_multiply(A22, B21, T, k, strideA, strideB, k);
    add_into(C21, T, k, strideC, k);

    recursive_multiply(A21, B12, C22, k, strideA, strideB, strideC);
    zero_block(T, k, k);
    recursive_multiply(A22, B22, T, k, strideA, strideB, k);
    add_into(C22, T, k, strideC, k);

    free_matrix(T);
}

void multiply_divide_conquer(int* A, int* B, int* C, int n) {
    recursive_multiply(A, B, C, n, n, n, n);
}

// ---------------- Strassen Multiplication ----------------
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}
void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int T1[k][k], T2[k][k];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];     A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];   A22[i][j] = A[i+k][j+k];
            B11[i][j] = B[i][j];     B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];   B22[i][j] = B[i+k][j+k];
        }
    }

    add(k, A11, A22, T1);  add(k, B11, B22, T2);  strassen(k, T1, T2, M1);
    add(k, A21, A22, T1);  strassen(k, T1, B11, M2);
    subtract(k, B12, B22, T2);  strassen(k, A11, T2, M3);
    subtract(k, B21, B11, T2);  strassen(k, A22, T2, M4);
    add(k, A11, A12, T1);  strassen(k, T1, B22, M5);
    subtract(k, A21, A11, T1);  add(k, B11, B12, T2);  strassen(k, T1, T2, M6);
    subtract(k, A12, A22, T1);  add(k, B21, B22, T2);  strassen(k, T1, T2, M7);

    add(k, M1, M4, T1); subtract(k, T1, M5, T2); add(k, T2, M7, C11);
    add(k, M3, M5, C12);
    add(k, M2, M4, C21);
    subtract(k, M1, M2, T1); add(k, T1, M3, T2); add(k, T2, M6, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }
}

// ---------------- Main Program ----------------
int main() {
    int n;
    printf("Enter size of square matrix (must be power of 2): ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C[n][n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    // Iterative
    clock_t start = clock();
    multiplyIterative(n, A, B, C);
    clock_t end = clock();
    printf("Iterative Method Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Divide & Conquer
    int* A1 = alloc_matrix(n), *B1 = alloc_matrix(n), *C1 = alloc_matrix(n);
    for (int i = 0; i < n*n; i++) { A1[i] = A[i/n][i%n]; B1[i] = B[i/n][i%n]; C1[i] = 0; }
    start = clock();
    multiply_divide_conquer(A1, B1, C1, n);
    end = clock();
    printf("Divide and Conquer Method Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    free_matrix(A1); free_matrix(B1); free_matrix(C1);

    // Strassen
    start = clock();
    strassen(n, A, B, C);
    end = clock();
    printf("Strassen Method Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}