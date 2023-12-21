#include <stdio.h>

// Linear Search
int linearSearch(int arr[], int size, int key, int *comparisons) {
    for (int i = 0; i < size; i++) {
        (*comparisons)++;
        if (arr[i] == key) {
            printf("Linear Search: Element found at index %d\n", i);
            return *comparisons;
        }
    }
    printf("Linear Search: Element not found\n");
    return *comparisons;
}

// Sentinel Linear Search
int sentinelLinearSearch(int arr[], int size, int key, int *comparisons) {
    int last = arr[size - 1];
    arr[size - 1] = key;

    int i = 0;
    while (arr[i] != key) {
        (*comparisons)++;
        i++;
    }

    arr[size - 1] = last;

    if (i < size - 1 || arr[size - 1] == key) {
        printf("Sentinel Linear Search: Element found at index %d\n", i);
    } else {
        printf("Sentinel Linear Search: Element not found\n");
    }

    return *comparisons;
}

// Binary Search
int binarySearch(int arr[], int size, int key, int *comparisons) {
    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        (*comparisons)++;

        if (arr[mid] == key) {
            printf("Binary Search: Element found at index %d\n", mid);
            return *comparisons;
        } else if (arr[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("Binary Search: Element not found\n");
    return *comparisons;
}

// Bubble Sort with comparisons and data transfer count
void bubbleSort(int arr[], int size) {
    int elementComparisons = 0;
    int dataTransferOperations = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            elementComparisons++;
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                dataTransferOperations += 3; // 3 data transfer operations for a swap
            }
        }
    }

    printf("Bubble Sort: Element Comparisons = %d, Data Transfer Operations = %d\n",
           elementComparisons, dataTransferOperations);
}

// Insertion Sort with comparisons and data transfer count
void insertionSort(int arr[], int size) {
    int elementComparisons = 0;
    int dataTransferOperations = 0;

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && key < arr[j]) {
            elementComparisons++;
            // Shift elements greater than key to the right
            arr[j + 1] = arr[j];
            dataTransferOperations++;
            j--;
        }

        arr[j + 1] = key;
        dataTransferOperations++;
    }

    printf("Insertion Sort: Element Comparisons = %d, Data Transfer Operations = %d\n",
           elementComparisons, dataTransferOperations);
}

int main() {
    // Example with integer array
    int intArray[] = {42, 15, 78, 23, 56, 91};
    int intSize = sizeof(intArray) / sizeof(int);
    printf("Original Integer Array: ");
    for (int i = 0; i < intSize; i++) {
        printf("%d ", intArray[i]);
    }
    printf("\n");

    bubbleSort(intArray, intSize);
    // Perform searches
    int linearComparisonsInt = linearSearch(intArray, intSize, 23, &linearComparisonsInt);
    int sentinelComparisonsInt = sentinelLinearSearch(intArray, intSize, 23, &sentinelComparisonsInt);
    int binaryComparisonsInt = binarySearch(intArray, intSize, 23, &binaryComparisonsInt);

    printf("\n");

    // Example with string array
    char *strArray[] = {"apple", "orange", "banana", "grape", "kiwi"};
    int strSize = sizeof(strArray) / sizeof(char *);
    printf("Original String Array: ");
    for (int i = 0; i < strSize; i++) {
        printf("%s ", strArray[i]);
    }
    printf("\n");

    insertionSort(strArray, strSize);
    // Perform searches
    int linearComparisonsStr = linearSearch(strArray, strSize, "banana", &linearComparisonsStr);
    int sentinelComparisonsStr = sentinelLinearSearch(strArray, strSize, "banana", &sentinelComparisonsStr);
    int binaryComparisonsStr = binarySearch(strArray, strSize, "banana", &binaryComparisonsStr);

    // Display total comparisons for each search
    printf("\nTotal Comparisons for Integer Searches:\n");
    printf("Linear Search: %d comparisons\n", linearComparisonsInt);
    printf("Sentinel Linear Search: %d comparisons\n", sentinelComparisonsInt);
    printf("Binary Search: %d comparisons\n", binaryComparisonsInt);

    return 0;
}
