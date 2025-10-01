#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h> 

/* allocate a square matrix (flat array) of size n x n */

int *alloc_matrix(int n) {

int *m = (int *)malloc(sizeof(int) * n * n);

if (!m) {

fprintf(stderr, "Memory allocation failed for %d x %d matrix\n", n, n);

exit(EXIT_FAILURE);

}

return m;

}

/* free matrix */

void free_matrix(int *m) {

free(m);

}

/* get element (i,j) from flat matrix with stride (row length) */

static inline int GET(int *M, int i, int j, int stride) {

return M[i * stride + j];

}

/* set element (i,j) */

static inline void SET(int *M, int i, int j, int stride, int val) {

M[i * stride + j] = val;

}

/* zero a n x n block pointed by M with given stride */

void zero_block(int *M, int n, int stride) {

for (int i = 0; i < n; ++i)

for (int j = 0; j < n; ++j) 



M[i * stride + j] = 0;

}

/* Add src (n x n) into dest: dest += src

dest_stride and src_stride are row lengths (stride) for their buffers */

void add_into(int *dest, int *src, int n, int dest_stride, int src_stride) {

for (int i = 0; i < n; ++i) {

int di = i * dest_stride;

int si = i * src_stride;

for (int j = 0; j < n; ++j) {

dest[di + j] += src[si + j];

}

}

}

/* Copy block src (n x n) to dest (n x n) with possible different strides */

void copy_block(int *dest, int *src, int n, int dest_stride, int src_stride) {

for (int i = 0; i < n; ++i) {

int di = i * dest_stride;

int si = i * src_stride;

for (int j = 0; j < n; ++j) {

dest[di + j] = src[si + j];

}

}

}

/*

Divide-and-conquer recursive multiplication: 



Computes C_block (n x n) = A_block (n x n) * B_block (n x n)

A_block pointer is A, B_block pointer is B, C_block pointer is C.

strideA, strideB, strideC are the row strides of their buffers.

*/

void recursive_multiply(int *A, int *B, int *C, int n, int strideA, int strideB, int strideC) {

if (n == 1) {

// single element multiplication

C[0] += A[0] * B[0];

return;

}

int k = n / 2;

// Pointers to sub-blocks inside A, B, C.

// A11 at A + 0, A12 at A + k, A21 at A + k*strideA, A22 at A + k*strideA + k

int *A11 = A;

int *A12 = A + k;

int *A21 = A + k * strideA;

int *A22 = A + k * strideA + k;

int *B11 = B;

int *B12 = B + k;

int *B21 = B + k * strideB;

int *B22 = B + k * strideB + k;

int *C11 = C;

int *C12 = C + k;

int *C21 = C + k * strideC;

int *C22 = C + k * strideC + k; 



// We'll compute:

// C11 = A11*B11 + A12*B21

// C12 = A11*B12 + A12*B22

// C21 = A21*B11 + A22*B21

// C22 = A21*B12 + A22*B22

// First zero the destination subblocks (they will be accumulated)

zero_block(C11, k, strideC);

zero_block(C12, k, strideC);

zero_block(C21, k, strideC);

zero_block(C22, k, strideC);

// Temporary block to hold the second product before adding

int *T = alloc_matrix(k); // contiguous k x k, stride = k

// Compute C11 = A11*B11

recursive_multiply(A11, B11, C11, k, strideA, strideB, strideC);

// Compute temp = A12*B21, then add into C11

zero_block(T, k, k);

recursive_multiply(A12, B21, T, k, strideA, strideB, k);

add_into(C11, T, k, strideC, k);

// C12 = A11*B12

recursive_multiply(A11, B12, C12, k, strideA, strideB, strideC);

// temp = A12*B22; add into C12

zero_block(T, k, k);

recursive_multiply(A12, B22, T, k, strideA, strideB, k);

add_into(C12, T, k, strideC, k);

// C21 = A21*B11 



recursive_multiply(A21, B11, C21, k, strideA, strideB, strideC);

// temp = A22*B21; add into C21

zero_block(T, k, k);

recursive_multiply(A22, B21, T, k, strideA, strideB, k);

add_into(C21, T, k, strideC, k);

// C22 = A21*B12

recursive_multiply(A21, B12, C22, k, strideA, strideB, strideC);

// temp = A22*B22; add into C22

zero_block(T, k, k);

recursive_multiply(A22, B22, T, k, strideA, strideB, k);

add_into(C22, T, k, strideC, k);

free_matrix(T);

}

/* next power of two >= x */

int next_power_of_two(int x) {

int p = 1;

while (p < x) p <<= 1;

return p;

}

/* multiply two n x n matrices given as A and B (row-major flat arrays),

result placed in C. Handles arbitrary n by padding to next power of two. */

void multiply_divide_conquer(int *A, int *B, int *C, int n) {

int m = next_power_of_two(n);

// allocate padded matrices (m x m)

int *Ap = alloc_matrix(m); 



int *Bp = alloc_matrix(m);

int *Cp = alloc_matrix(m);

// zero padded arrays

for (int i = 0; i < m * m; ++i) { Ap[i] = 0; Bp[i] = 0; Cp[i] = 0; }

// copy A and B into top-left of Ap and Bp

for (int i = 0; i < n; ++i)

for (int j = 0; j < n; ++j) {

Ap[i * m + j] = A[i * n + j]; // careful: source stride is n, dest stride is m

Bp[i * m + j] = B[i * n + j];

}

// perform recursive multiply on m x m blocks (stride = m)

recursive_multiply(Ap, Bp, Cp, m, m, m, m);

// copy top-left n x n of Cp into C (destination stride is n, source stride is m)

for (int i = 0; i < n; ++i)

for (int j = 0; j < n; ++j)

C[i * n + j] = Cp[i * m + j];

free_matrix(Ap);

free_matrix(Bp);

free_matrix(Cp);

}

/* utility print (for small matrices) */

void print_matrix(int *M, int n) {

for (int i = 0; i < n; ++i) {

for (int j = 0; j < n; ++j)

printf("%d ", M[i * n + j]); 



printf("\n");

}

}

int main() {

int n;

printf("Enter size n of square matrices: ");

if (scanf("%d", &n) != 1 || n <= 0) {

fprintf(stderr, "Invalid n\n");

return 1;

}

// allocate input and output matrices (n x n)

int *A = alloc_matrix(n);

int *B = alloc_matrix(n);

int *C = alloc_matrix(n);

// fill A and B with random small integers

srand((unsigned)time(NULL));

for (int i = 0; i < n * n; ++i) {

A[i] = rand() % 10; // values 0..9

B[i] = rand() % 10;

C[i] = 0;

}

// If n is small, print A and B for verification

if (n <= 8) {

printf("Matrix A:\n"); print_matrix(A, n);

printf("Matrix B:\n"); print_matrix(B, n); 



}

clock_t start = clock();

multiply_divide_conquer(A, B, C, n);

clock_t end = clock();

double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

// print result (small n) and time

if (n <= 8) {

printf("Product C = A * B:\n"); print_matrix(C, n);

}

printf("Divide-and-Conquer Multiplication for %d x %d took %f seconds\n", n, n, time_taken);

free_matrix(A);

free_matrix(B);

free_matrix(C);

return 0;

}
