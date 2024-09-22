#include <stdio.h>

void merge(int a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void sort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        sort(a, l, m);
        sort(a, m + 1, r);

        merge(a, l, m, r);
    }
}

void print(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {12, 11, 23, 7, 8, 9, 1, 2};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Given array is \n");
    print(a, n);

    sort(a, 0, n - 1);

    printf("\nSorted array is \n");
    print(a, n);
    return 0;
}
