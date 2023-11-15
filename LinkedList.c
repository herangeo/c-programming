#include <stdio.h>
#include <stdlib.h>

struct member {
    char name[50];
    int age;
    char membershipType[20];
    struct member *next;
};

struct member *head;

void addMember();
void removeMember();
void displayMembers();
void searchMember();
void exitProgram();
void randomDelete();

int main() {
    int choice = 0;
    while (choice != 5) {
        printf("\n\n*********Gym Management System*********\n");
        printf("Choose one option from the following list ...\n");
        printf("===============================================\n");
        printf("1. Add Member\n");
        printf("2. Remove Member\n");
        printf("3. Display Members\n");
        printf("4. Delete Random element\n");
        printf("5. Exit\n");
        printf("Enter your choice?\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                removeMember();
                break;
            case 3:
                displayMembers();
                break;
            case 4:
                randomDelete();
                break;
            case 5:
                exitProgram();
                break;
            default:
                printf("Please enter a valid choice.\n");
        }
    }

    return 0;
}

void addMember() {
    struct member *ptr = (struct member *)malloc(sizeof(struct member));
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
    } else {
        printf("Enter member's name: ");
        scanf("%s", ptr->name);
        printf("Enter member's age: ");
        scanf("%d", &ptr->age);
        printf("Enter membership type: ");
        scanf("%s", ptr->membershipType);

        ptr->next = head;
        head = ptr;

        printf("Member added successfully.\n");
    }
}

void removeMember() {
char memberName[50];
    printf("Enter the name of the member to remove: ");
    scanf("%s", memberName);

    struct member *current = head;
    struct member *previous = NULL;

    while (current != NULL && (current->name == memberName) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Member not found.\n");
    } else {
        if (previous == NULL) {
            // If the member to be removed is the head
            head = current->next;
        } else {
            previous->next = current->next;
        }

        free(current);
        printf("Member removed successfully.\n");
    }
}

void displayMembers() {
    struct member *ptr = head;
    if (ptr == NULL) {
        printf("No members to display.\n");
    } else {
        printf("\n*********Members List*********\n");
        while (ptr != NULL) {
            printf("Name: %s, Age: %d, Membership Type: %s\n", ptr->name, ptr->age, ptr->membershipType);
            ptr = ptr->next;
        }
    }
}

void searchMember() {
     char memberName[50];
    printf("Enter the name of the member to search: ");
    scanf("%s", memberName);

    struct member *current = head;
    int found = 0;

    while (current != NULL) {
        if (current->name == memberName) {
            printf("Member found - Name: %s, Age: %d, Membership Type: %s\n", current->name, current->age, current->membershipType);
            found = 1;
            break;
        }

        current = current->next;
    }

    if (!found) {
        printf("Member not found.\n");
    }
}

void exitProgram() {
    struct member *current = head;
    struct member *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    printf("Memory freed. Exiting program.\n");
    exit(0);
}
void randomDelete() {
    int prevIndex, count = 0;
    printf("Enter the location of the node after which you want to perform deletion: ");
    scanf("%d", &prevIndex);

    struct member *current = head;
    struct member *previous = NULL;

    while (current != NULL && count != prevIndex) {
        previous = current;
        current = current->next;
        count++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Invalid index. Member not found or no member after the specified index.\n");
    } else {
        struct member *toBeDeleted = current->next;
        current->next = toBeDeleted->next;

        free(toBeDeleted);
        printf("Member after index %d removed successfully.\n", prevIndex);
    }
}




