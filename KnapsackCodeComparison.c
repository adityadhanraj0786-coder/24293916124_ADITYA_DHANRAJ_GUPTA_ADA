#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Data for 8 items
int weights[] = {10, 5, 15, 7, 6, 18, 3, 12};
int profits[] = {60, 30, 100, 50, 40, 90, 20, 80};
int n = 8;

// Fractional Knapsack (Greedy)
float fractionalKnapsack(int capacity) {
    float totalProfit = 0;
    int currentWeight = 0;
    for (int loop = 0; loop < 100000; loop++) {
        totalProfit = 0;
        currentWeight = 0;
        // Sort by ratio each iteration if needed, omitted for brevity
        for (int i = 0; i < n; i++) {
            if (currentWeight + weights[i] <= capacity) {
                currentWeight += weights[i];
                totalProfit += profits[i];
            } else if (currentWeight < capacity) {
                int rem = capacity - currentWeight;
                totalProfit += profits[i] * ((float)rem / weights[i]);
                break;
            }
        }
    }
    return totalProfit;
}

// 0/1 Knapsack (DP)
int knapsack01(int capacity, int *spaceUsed) {
    *spaceUsed = (n + 1) * (capacity + 1) * sizeof(int);
    int maxProfit = 0;
    for (int loop = 0; loop < 10000; loop++) {
        int **dp = malloc((n + 1) * sizeof(int *));
        for (int i = 0; i <= n; i++) {
            dp[i] = malloc((capacity + 1) * sizeof(int));
        }
        for (int i = 0; i <= n; i++) {
            for (int w = 0; w <= capacity; w++) {
                if (i == 0 || w == 0) {
                    dp[i][w] = 0;
                } else if (weights[i - 1] <= w) {
                    int include = profits[i - 1] + dp[i - 1][w - weights[i - 1]];
                    int exclude = dp[i - 1][w];
                    dp[i][w] = (include > exclude) ? include : exclude;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        maxProfit = dp[n][capacity];
        for (int i = 0; i <= n; i++) {
            free(dp[i]);
        }
        free(dp);
    }
    return maxProfit;
}

int main() {
    int capacity;
    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    // Display items
    printf("\nItems Data:\n");
    printf("Item\tWeight\tProfit\tRatio\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%.2f\n", i + 1, weights[i], profits[i],
               (float)profits[i] / weights[i]);
    }

    // Fractional metrics
    int sp_frac = n * sizeof(int) * 3;  // ~ size of weights, profits, ratio arrays
    clock_t t_start1 = clock();
    float profit_frac = fractionalKnapsack(capacity);
    double time_frac = (double)(clock() - t_start1) / CLOCKS_PER_SEC;

    // 0/1 DP metrics
    int sp_dp;
    clock_t t_start2 = clock();
    int profit_dp = knapsack01(capacity, &sp_dp);
    double time_dp = (double)(clock() - t_start2) / CLOCKS_PER_SEC;

    // Comparison Table
    printf("\nComparison Table:\n");
    printf("Algo\t\tProfit\tTime(sec)\tSpace(bytes)\n");
    printf("-----\t\t------\t---------\t------------\n");
    printf("Fractional\t%.2f\t%.6f\t%d\n", profit_frac, time_frac, sp_frac);
    printf("0/1 DP\t\t%d\t%.6f\t%d\n", profit_dp, time_dp, sp_dp);

    return 0;
}
