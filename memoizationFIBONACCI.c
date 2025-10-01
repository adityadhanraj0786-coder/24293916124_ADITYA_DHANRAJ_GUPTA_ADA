#include <stdio.h>
#include <windows.h>
long long fib_memo_helper(int n, long long memo[]) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_memo_helper(n - 1, memo) + fib_memo_helper(n - 2, memo);
    return memo[n];
}
int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    long long memo[n + 1];
    for (int i = 0; i <= n; ++i) memo[i] = -1;
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    fib_memo_helper(n, memo);
    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    size_t space_used = sizeof(memo) + (sizeof(int) + sizeof(long long)) * n;
    printf("\nExecution Time: %.9f seconds\n", time_taken);
    printf("Approx. Space Used: %zu bytes (array + stack)\n", space_used);
    return 0;
}
