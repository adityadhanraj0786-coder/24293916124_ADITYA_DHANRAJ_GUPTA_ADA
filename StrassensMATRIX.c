#include <stdio.h>

#include <stdlib.h>

#include <time.h>

// Function to add matrices

void add(int n, int A[n][n], int B[n][n], int C[n][n]) {

for (int i = 0; i < n; i++)

for (int j = 0; j < n; j++)

C[i][j] = A[i][j] + B[i][j];

} 



// Function to subtract matrices

void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {

for (int i = 0; i < n; i++)

for (int j = 0; j < n; j++)

C[i][j] = A[i][j] - B[i][j];

}

// Strassen recursive multiplication

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

// Dividing matrices into quadrants

for (int i = 0; i < k; i++) {

for (int j = 0; j < k; j++) {

A11[i][j] = A[i][j];

A12[i][j] = A[i][j+k];

A21[i][j] = A[i+k][j];

A22[i][j] = A[i+k][j+k];

B11[i][j] = B[i][j];

B12[i][j] = B[i][j+k]; 



B21[i][j] = B[i+k][j];

B22[i][j] = B[i+k][j+k];

}

}

// M1 = (A11 + A22)(B11 + B22)

add(k, A11, A22, T1);

add(k, B11, B22, T2);

strassen(k, T1, T2, M1);

// M2 = (A21 + A22)B11

add(k, A21, A22, T1);

strassen(k, T1, B11, M2);

// M3 = A11(B12 - B22)

subtract(k, B12, B22, T2);

strassen(k, A11, T2, M3);

// M4 = A22(B21 - B11)

subtract(k, B21, B11, T2);

strassen(k, A22, T2, M4);

// M5 = (A11 + A12)B22

add(k, A11, A12, T1);

strassen(k, T1, B22, M5);

// M6 = (A21 - A11)(B11 + B12)

subtract(k, A21, A11, T1);

add(k, B11, B12, T2);

strassen(k, T1, T2, M6);

// M7 = (A12 - A22)(B21 + B22)

subtract(k, A12, A22, T1);

add(k, B21, B22, T2); 



strassen(k, T1, T2, M7);

// C11 = M1 + M4 - M5 + M7

add(k, M1, M4, T1);

subtract(k, T1, M5, T2);

add(k, T2, M7, C11);

// C12 = M3 + M5

add(k, M3, M5, C12);

// C21 = M2 + M4

add(k, M2, M4, C21);

// C22 = M1 - M2 + M3 + M6

subtract(k, M1, M2, T1);

add(k, T1, M3, T2);

add(k, T2, M6, C22);

// Combining quadrants into result matrix

for (int i = 0; i < k; i++) {

for (int j = 0; j < k; j++) {

C[i][j] = C11[i][j];

C[i][j+k] = C12[i][j];

C[i+k][j] = C21[i][j];

C[i+k][j+k] = C22[i][j];

}

}

}

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

clock_t start = clock();

strassen(n, A, B, C);

clock_t end = clock();



double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

printf("Strassen Method Time for %d x %d matrix: %f seconds\n", n, n, time_taken);

return 0;

}
