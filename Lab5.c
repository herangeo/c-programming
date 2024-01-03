#include <stdio.h>

// Function prototypes
int linearSearch(int arr[], int size, int key, int* elementComparisons, int* indexComparisons);
int sentinelSearch(int arr[], int size, int key, int* elementComparisons, int* indexComparisons);
int binarySearch(int arr[], int size, int key, int* elementComparisons, int* indexComparisons);
void bubbleSort(int arr[], int size, int* comparisons, int* transfers);
void insertionSort(int arr[], int size, int* comparisons, int* transfers);
void printArray(int arr[], int size);

int main() {
    int size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter %d elements for the array:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Display original array
    printf("\nOriginal Array: ");
    printArray(arr, size);

    // Linear Search
    int keyLinear;
    printf("\nEnter the key for Linear Search: ");
    scanf("%d", &keyLinear);

    int elementComparisonsLinear = 0, indexComparisonsLinear = 0;
    linearSearch(arr, size, keyLinear, &elementComparisonsLinear, &indexComparisonsLinear);
    printf("\nLinear Search - Element Comparisons: %d, Index Comparisons: %d\n", elementComparisonsLinear, indexComparisonsLinear);

    // Sentinel Search
    int keySentinel;
    printf("\nEnter the key for Sentinel Search: ");
    scanf("%d", &keySentinel);

    int elementComparisonsSentinel = 0, indexComparisonsSentinel = 0;
    sentinelSearch(arr, size, keySentinel, &elementComparisonsSentinel, &indexComparisonsSentinel);
    printf("\nSentinel Search - Element Comparisons: %d, Index Comparisons: %d\n", elementComparisonsSentinel, indexComparisonsSentinel);

    // Bubble Sort
    int bubbleComparisons = 0, bubbleTransfers = 0;
    bubbleSort(arr, size, &bubbleComparisons, &bubbleTransfers);
    printf("\nSorted Array using Bubble Sort: ");
    printArray(arr, size);
    printf("Bubble Sort - Comparisons: %d, Data Transfer Operations: %d\n", bubbleComparisons, bubbleTransfers);

    // Binary Search (Requires a sorted array)
    int keyBinary;
    printf("\nEnter the key for Binary Search: ");
    scanf("%d", &keyBinary);

    int elementComparisonsBinary = 0, indexComparisonsBinary = 0;
    // Performing Binary Search
    binarySearch(arr, size, keyBinary, &elementComparisonsBinary, &indexComparisonsBinary);
    printf("\nBinary Search - Element Comparisons: %d, Index Comparisons: %d\n", elementComparisonsBinary, indexComparisonsBinary);

    // Display sorted array after sorting
    printf("\nSorted Array: ");
    printArray(arr, size);

    // Insertion Sort
    int insertionComparisons = 0, insertionTransfers = 0;
    insertionSort(arr, size, &insertionComparisons, &insertionTransfers);
    printf("\nSorted Array using Insertion Sort: ");
    printArray(arr, size);
    printf("Insertion Sort - Comparisons: %d, Data Transfer Operations: %d\n", insertionComparisons, insertionTransfers);

    return 0;
}

// Linear Search
int linearSearch(int arr[], int size, int key, int* elementComparisons, int* indexComparisons) {
    for (int i = 0; i < size; i++) {
        (*elementComparisons)++;
        if (arr[i] == key) {
            (*indexComparisons)++;
            return i; // Element found
        }
    }
    return -1; // Element not found
}

// Sentinel Search
int sentinelSearch(int arr[], int size, int key, int* elementComparisons, int* indexComparisons) {
    int lastElement = arr[size - 1];
    arr[size - 1] = key; // Set sentinel

    int i = 0;
    while (arr[i] != key) {
        (*elementComparisons)++;
        i++;
    }

    arr[size - 1] = lastElement; // Restore the last element
    if (i < size - 1 || key == lastElement) {
        (*indexComparisons)++;
        return i; // Element found
    }

    return -1; // Element not found
}

// Binary Search
int binarySearch(int arr[], int size, int key, int* elementComparisons, int* indexComparisons) {
    int low = 0, high = size - 1;
    while (low <= high) {
        (*indexComparisons)++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            (*elementComparisons)++;
            return mid; // Element found
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Element not found
}

// Bubble Sort
void bubbleSort(int arr[], int size, int* comparisons, int* transfers) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                (*transfers)++;
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int size, int* comparisons, int* transfers) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        (*comparisons)++;
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            (*transfers)++;
            arr[j + 1] = arr[j];
            j--;
        }
        (*transfers)++;
        arr[j + 1] = key;
    }
}

// Display array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
