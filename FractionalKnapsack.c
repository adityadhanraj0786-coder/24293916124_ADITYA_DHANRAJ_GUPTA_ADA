#include <stdio.h>

typedef struct {
    float weight;
    float value;
    float ratio;
} Item;

void sortItemsByRatio(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].ratio > items[i].ratio) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void fractionalKnapsack(Item items[], int n, float capacity) {
    sortItemsByRatio(items, n);

    float totalValue = 0.0;
    for (int i = 0; i < n && capacity > 0; i++) {
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take fraction of the last item fitting into knapsack
            totalValue += items[i].ratio * capacity;
            capacity = 0;
        }
    }
    printf("Maximum value achievable = %.2f\n", totalValue);
}

int main() {
    int n;
    float capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of items must be positive.\n");
        return 1;
    }

    Item items[n];

    for (int i = 0; i < n; i++) {
        printf("Enter weight and value for item %d: ", i + 1);
        scanf("%f %f", &items[i].weight, &items[i].value);
        if (items[i].weight <= 0) {
            printf("Weight must be positive.\n");
            return 1;
        }
        items[i].ratio = items[i].value / items[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);
    if (capacity <= 0) {
        printf("Capacity must be positive.\n");
        return 1;
    }

    fractionalKnapsack(items, n, capacity);

    return 0;
}

