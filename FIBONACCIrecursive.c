#include <stdio.h>
#include <windows.h>
long long fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}
int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    fib_recursive(n);
    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    size_t space_used = n * (sizeof(int) + sizeof(long long)); // approx stack space
    printf("\nExecution Time: %.9f seconds\n", time_taken);
    printf("Approx. Space Used: %zu bytes (stack frames)\n", space_used);
    return 0;
}

