#include <stdio.h>

int subset[20], n, total = 0;

void findSubset(int weights[], int currentSum, int currentIndex, int remainingSum) {
    if (currentSum == total) {
        printf("Subset found: ");
        for (int i = 0; i < currentIndex; i++) {
            if (subset[i] == 1) {
                printf("%d ", weights[i]);
            }
        }
        printf("\n");
        return;
    }

    if (currentSum > total || currentIndex >= n) {
        return;
    }

    subset[currentIndex] = 1;
    findSubset(weights, currentSum + weights[currentIndex], currentIndex + 1, remainingSum - weights[currentIndex]);

    subset[currentIndex] = 0;
    findSubset(weights, currentSum, currentIndex + 1, remainingSum - weights[currentIndex]);
}

int main() {
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int weights[n], totalWeight = 0;
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
        totalWeight += weights[i];
    }

    printf("Enter the desired total sum: ");
    scanf("%d", &total);

    if (total > totalWeight) {
        printf("No solution possible as the total sum exceeds the sum of all elements.\n");
        return 0;
    }

    findSubset(weights, 0, 0, totalWeight);

    return 0;
}
