#include <stdio.h>

void knapsackGreedy(int n, int weight[], int value[], int capacity) {
    double ratio[n];
    int i, j;
    for (i = 0; i < n; i++) {
        ratio[i] = (double)value[i] / weight[i];
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                double tempRatio = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = tempRatio;

                int tempWeight = weight[i];
                weight[i] = weight[j];
                weight[j] = tempWeight;

                int tempValue = value[i];
                value[i] = value[j];
                value[j] = tempValue;
            }
        }
    }

    int totalValue = 0, currentWeight = 0;
    for (i = 0; i < n; i++) {
        if (currentWeight + weight[i] <= capacity) {
            currentWeight += weight[i];
            totalValue += value[i];
        }
    }

    printf("Greedy Approach: Total Value = %d\n", totalValue);
}

void knapsackDP(int n, int weight[], int value[], int capacity) {
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weight[i - 1] <= w) {
                dp[i][w] = (value[i - 1] + dp[i - 1][w - weight[i - 1]] > dp[i - 1][w]) 
                            ? value[i - 1] + dp[i - 1][w - weight[i - 1]] 
                            : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("Dynamic Programming Approach: Total Value = %d\n", dp[n][capacity]);
}

int main() {
    int n, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int weight[n], value[n];

    printf("Enter the weights and values of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &weight[i], &value[i]);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    knapsackGreedy(n, weight, value, capacity);
    knapsackDP(n, weight, value, capacity);

    return 0;
}
