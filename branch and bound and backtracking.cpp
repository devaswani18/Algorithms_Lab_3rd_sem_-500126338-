#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming Approach
int knapsackDP(int n, int weights[], int values[], int capacity) {
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

// Backtracking Approach
int knapsackBacktracking(int n, int weights[], int values[], int capacity, int currentIndex, int currentWeight, int currentValue, int *maxValue) {
    if (currentIndex == n) {
        if (currentValue > *maxValue) {
            *maxValue = currentValue;
        }
        return *maxValue;
    }

    if (currentWeight + weights[currentIndex] <= capacity) {
        knapsackBacktracking(n, weights, values, capacity, currentIndex + 1, currentWeight + weights[currentIndex], currentValue + values[currentIndex], maxValue);
    }

    knapsackBacktracking(n, weights, values, capacity, currentIndex + 1, currentWeight, currentValue, maxValue);

    return *maxValue;
}

// Branch & Bound Approach
typedef struct Node {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

float calculateBound(Node u, int n, int capacity, int weights[], int values[]) {
    if (u.weight >= capacity) return 0;

    float bound = u.profit;
    int totalWeight = u.weight;
    for (int i = u.level + 1; i < n; i++) {
        if (totalWeight + weights[i] <= capacity) {
            totalWeight += weights[i];
            bound += values[i];
        } else {
            bound += (capacity - totalWeight) * ((float)values[i] / weights[i]);
            break;
        }
    }
    return bound;
}

int knapsackBranchAndBound(int n, int weights[], int values[], int capacity) {
    Node queue[100];
    int front = -1, rear = -1;

    Node u, v;
    int maxProfit = 0;

    v.level = -1;
    v.profit = 0;
    v.weight = 0;
    v.bound = calculateBound(v, n, capacity, weights, values);
    queue[++rear] = v;

    while (front != rear) {
        u = queue[++front];

        if (u.bound > maxProfit) {
            v.level = u.level + 1;

            v.weight = u.weight + weights[v.level];
            v.profit = u.profit + values[v.level];

            if (v.weight <= capacity && v.profit > maxProfit) {
                maxProfit = v.profit;
            }
            v.bound = calculateBound(v, n, capacity, weights, values);
            if (v.bound > maxProfit) {
                queue[++rear] = v;
            }

            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = calculateBound(v, n, capacity, weights, values);
            if (v.bound > maxProfit) {
                queue[++rear] = v;
            }
        }
    }
    return maxProfit;
}

int main() {
    int n, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int weights[n], values[n];
    printf("Enter the weights and values of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &weights[i], &values[i]);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    int maxValue = 0;
    printf("Dynamic Programming Approach: %d\n", knapsackDP(n, weights, values, capacity));
    printf("Backtracking Approach: %d\n", knapsackBacktracking(n, weights, values, capacity, 0, 0, 0, &maxValue));
    printf("Branch & Bound Approach: %d\n", knapsackBranchAndBound(n, weights, values, capacity));

    return 0;
}
