#include <stdio.h>
#include <windows.h>

long long fib_bottomup(int n)
{
    if (n <= 1)
        return n;
    long long dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int main(void)
{
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0)
        return 1;

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    long long result = fib_bottomup(n);
    QueryPerformanceCounter(&end);

    double timetaken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    size_t spaceused = sizeof(long long) * (n + 1) + sizeof(int);

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time: %.9f seconds\n", timetaken);
    printf("Approx. Space Used: %zu bytes (array + int)\n", spaceused);

    return 0;
}