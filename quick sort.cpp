#include <stdio.h>

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int array[], int start, int end) {
    int pivot = array[end];  
    int index = (start - 1);      

    for (int current = start; current < end; current++) {
        if (array[current] <= pivot) {
            index++;  
            swap(&array[index], &array[current]);
        }
    }
    swap(&array[index + 1], &array[end]);
    return (index + 1);
}

void quickSort(int array[], int start, int end) {
    if (start < end) {
        int pivot = partition(array, start, end);

        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}

void display(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int size;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int elements[size];

    printf("Enter the elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &elements[i]);
    }

    quickSort(elements, 0, size - 1);

    printf("Sorted array: \n");
    display(elements, size);

    return 0;
}
