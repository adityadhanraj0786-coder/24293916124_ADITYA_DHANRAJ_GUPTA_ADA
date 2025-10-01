#include <stdio.h>
#include <windows.h>
long long fib_iterative(int n) {
    if (n <= 1) return n;
    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; ++i) {
        long long curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    fib_iterative(n);
    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    size_t space_used = sizeof(long long) * 3 + sizeof(int);
    printf("\nExecution Time: %.9f seconds\n", time_taken);
    printf("Approx. Space Used: %zu bytes (locals only)\n", space_used);
    return 0;
}

