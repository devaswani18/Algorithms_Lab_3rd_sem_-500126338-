#include <stdio.h>

void activitySelection(int start[], int finish[], int n) {
    int i, j;
    printf("Selected activities: ");
    i = 0;
    printf("%d ", i);

    for (j = 1; j < n; j++) {
        if (start[j] >= finish[i]) {
            printf("%d ", j);
            i = j;
        }
    }
    printf("\n");
}

int main() {
    int n, i;
    printf("Enter the number of activities: ");
    scanf("%d", &n);

    int start[n], finish[n];
    printf("Enter the start times of activities:\n");
    for (i = 0; i < n; i++) {
        printf("Activity %d start time: ", i);
        scanf("%d", &start[i]);
    }

    printf("Enter the finish times of activities:\n");
    for (i = 0; i < n; i++) {
        printf("Activity %d finish time: ", i);
        scanf("%d", &finish[i]);
    }

    activitySelection(start, finish, n);
    return 0;
}
