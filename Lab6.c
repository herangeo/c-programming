#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent workout data
struct WorkoutData {
    int workoutValue;
};

// Function prototypes
void quickSort(struct WorkoutData arr[], int low, int high, int* quickComparisons);
void bubbleSort(struct WorkoutData arr[], int size, int* bubbleComparisons);
int partition(struct WorkoutData arr[], int low, int high, int* quickComparisons);
void swap(struct WorkoutData* a, struct WorkoutData* b);
void generateRandomData(struct WorkoutData arr[], int size);
void writeDataToFile(struct WorkoutData arr[], int size, const char* filename);
void readDataFromFile(struct WorkoutData arr[], int size, const char* filename);
void printArray(struct WorkoutData arr[], int size);

int main() {
    const int size = 5;
    struct WorkoutData workoutDataQuick[size];
    struct WorkoutData workoutDataBubble[size];

    // Generate random numerical data
    generateRandomData(workoutDataQuick, size);
    // Copy data for Bubble Sort
    for (int i = 0; i < size; i++) {
        workoutDataBubble[i] = workoutDataQuick[i];
    }

    // Display original data
    printf("Original Workout Data: ");
    printArray(workoutDataQuick, size);

    // Sort the workout data using Quick Sort
    int quickComparisons = 0;
    quickSort(workoutDataQuick, 0, size - 1, &quickComparisons);
    // Display sorted data using Quick Sort
    printf("\nSorted Workout Data (Quick Sort): ");
    printArray(workoutDataQuick, size);
    printf("Number of comparisons (Quick Sort): %d\n", quickComparisons);

    // Sort the workout data using Bubble Sort
    int bubbleComparisons = 0;
    bubbleSort(workoutDataBubble, size, &bubbleComparisons);
    // Display sorted data using Bubble Sort
    printf("\nSorted Workout Data (Bubble Sort): ");
    printArray(workoutDataBubble, size);
    printf("Number of comparisons (Bubble Sort): %d\n", bubbleComparisons);

    // Check and display which sort was better
    if (quickComparisons < bubbleComparisons) {
        printf("\nQuick Sort performed better than Bubble Sort in terms of comparisons.\n");
    } else if (quickComparisons > bubbleComparisons) {
        printf("\nBubble Sort performed better than Quick Sort in terms of comparisons.\n");
    } else {
        printf("\nThe number of comparisons made by Quick Sort and Bubble Sort is equal.\n");
    }

    return 0;
}

// Quick Sort implementation
void quickSort(struct WorkoutData arr[], int low, int high, int* quickComparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, quickComparisons);

        quickSort(arr, low, pi - 1, quickComparisons);
        quickSort(arr, pi + 1, high, quickComparisons);
    }
}

// Bubble Sort implementation
void bubbleSort(struct WorkoutData arr[], int size, int* bubbleComparisons) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            (*bubbleComparisons)++;
            if (arr[j].workoutValue > arr[j + 1].workoutValue) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


// Partition function for Quick Sort
int partition(struct WorkoutData arr[], int low, int high, int* quickComparisons) {
    int pivot = arr[high].workoutValue;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*quickComparisons)++;
        if (arr[j].workoutValue < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}




void swap(struct WorkoutData* a, struct WorkoutData* b) {
    struct WorkoutData temp = *a;
    *a = *b;
    *b = temp;
}

// Generate random numerical data for workout
void generateRandomData(struct WorkoutData arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i].workoutValue = rand() % 20; // Assuming a range of 0 to 19 for workout values
    }
}

// Write data to a file using structures
void writeDataToFile(struct WorkoutData arr[], int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < size; i++) {
            fprintf(file, "%d\n", arr[i].workoutValue);
        }
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

// Read data from a file using structures
void readDataFromFile(struct WorkoutData arr[], int size, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        for (int i = 0; i < size; i++) {
            fscanf(file, "%d", &arr[i].workoutValue);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}

// Print array elements
void printArray(struct WorkoutData arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i].workoutValue);
    }
    printf("\n");
}