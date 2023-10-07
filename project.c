#include <stdio.h>

int Menu();
void Park(int type);
void Exit();
void ShowDetail();
void DisplayParkingMap();
void ShowAvailableSlots();
void WelcomeMessage();
void SaveDataToFile();
void LoadDataFromFile();

int nor = 0, nob = 0, noc = 0, count = 0;
int id = 1001;
int usedIDs[1500] = {0};

int main() {
    LoadDataFromFile(); // Load data from file at the beginning
    WelcomeMessage();

    while (1) {
        switch (Menu()) {
            case 1:
                Park(1);
                break;
            case 2:
                Park(2);
                break;
            case 3:
                Park(3);
                break;
            case 4:
                ShowDetail();
                break;
            case 5:
                Exit();
                break;
            case 6:
                ShowAvailableSlots();
                break;
            case 7:
                DisplayParkingMap();
                break;
            case 8:
                SaveDataToFile(); // Save data to file before exiting
                return 0; // Exit the program
            default:
                printf("\nInvalid choice :");
        }
        getchar();
    }
}

int Menu() {
    int ch;
    printf("\n");
    printf("\n1. Enter bike: ");
    printf("\n2. Enter cycle: ");
    printf("\n3. Enter car: ");
    printf("\n4. Show Status:");
    printf("\n5. Exit:");
    printf("\n6. Show Available Slots:");
    printf("\n7. Display Parking Map:");
    printf("\n8. Quit:");
    printf("\n\nEnter your choice :\n");
    scanf("%d", &ch);
    return ch;
}

void WelcomeMessage() {
    printf("Welcome to Christ College Parking Management System!\n");
}

void Park(int type) {
    printf("\nEnter ID: ");
    int entryID;
    scanf("%d", &entryID);

    for (int i = 0; i < 1500; i++) {
        if (usedIDs[i] == entryID) {
            printf("\nID %d has already been parked. You can't park more than one vehicle with the same ID.", entryID);
            return;
        }
    }

    int parkingSlot;
    switch (type) {
        case 1:
            parkingSlot = nob + 1;
            break;
        case 2:
            parkingSlot = 500 + noc + 1;
            break;
        case 3:
            parkingSlot = 1000 + nor + 1;
            break;
        default:
            return;
    }

    if (parkingSlot <= 1500) {
        usedIDs[parkingSlot - 1] = entryID;
        printf("\nEntry successful for ID %d. Park at slot %d", entryID, parkingSlot);
        switch (type) {
            case 1: nob++; break;
            case 2: noc++; break;
            case 3: nor++; break;
        }
        count++;
    } else {
        printf("\nNo available parking slots for type %d", type);
    }
}

void Exit() {
    int removeSlot;
    printf("\nEnter slot number to remove vehicle: ");
    scanf("%d", &removeSlot);

    if (removeSlot > 0 && removeSlot <= 1500) {
        int removeID = usedIDs[removeSlot - 1];
        if (removeID != 0) {
            usedIDs[removeSlot - 1] = 0;
            if (removeSlot <= 500) {
                nob--;
            } else if (removeSlot <= 1000) {
                noc--;
            } else {
                nor--;
            }
            count--;
            printf("\nVehicle with ID %d removed successfully from slot %d.", removeID, removeSlot);
        } else {
            printf("\nNo vehicle found at slot %d", removeSlot);
        }
    } else {
        printf("\nInvalid slot number");
    }
}

void ShowDetail() {
    printf("\nNumber of bike = %d", nob);
    printf("\nNumber of Cycle = %d", noc);
    printf("\nNumber of Car = %d", nor);
    printf("\nTotal number of vehicles = %d", count);
}

void DisplayParkingMap() {
    printf("\nParking Map:\n");
    for (int i = 0; i < 1500; i += 3) {
        printf("| %3d: %4s | %3d: %4s | %3d: %4s |\n",
               i + 1, usedIDs[i] ? "X" : "Free",
               i + 2, usedIDs[i+1] ? "X" : "Free",
               i + 3, usedIDs[i+2] ? "X" : "Free");
    }
}

void ShowAvailableSlots() {
    printf("\nAvailable Slots:");
    printf("\n- Bus: %d", 500 - nob);
    printf("\n- Cycle: %d", 500 - noc);
    printf("\n- Riksha: %d", 500 - nor);
}

void SaveDataToFile() {
    FILE *file = fopen("parking_data.txt", "w");

    if (file != NULL) {
        fprintf(file, "%d %d %d %d\n", nor, nob, noc, count);
        for (int i = 0; i < 1500; i++) {
            fprintf(file, "%d ", usedIDs[i]);
        }

        fclose(file);
        printf("Data saved to file.\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

void LoadDataFromFile() {
    FILE *file = fopen("parking_data.txt", "r");

    if (file != NULL) {
        fscanf(file, "%d %d %d %d", &nor, &nob, &noc, &count);
        for (int i = 0; i < 1500; i++) {
            fscanf(file, "%d", &usedIDs[i]);
        }

        fclose(file);
        printf("Data loaded from file.\n");
    } else {
        printf("Error opening file for reading. Starting with default values.\n");
    }
}


