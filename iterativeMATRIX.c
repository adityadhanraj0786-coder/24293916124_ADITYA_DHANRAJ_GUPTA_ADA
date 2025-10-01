#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Function to multiply matrices iteratively
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
int main() {
    int n;
    printf("Enter size of square matrix (n): ");
    scanf("%d", &n);
    int A[n][n], B[n][n], C[n][n];
    srand(time(NULL));
    // Initializing random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    clock_t start = clock();
    multiplyIterative(n, A, B, C);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iterative Method Time for %d x %d matrix: %f seconds\n", n, n, time_taken);
    return 0;
}
