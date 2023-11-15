#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("4. Random Deletion\n");
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

        if (head == NULL) {
            // First member
            head = ptr;
            ptr->next = head;
        } else {
            // Insert at the end and update linking
            struct member *last = head;
            while (last->next != head) {
                last = last->next;
            }

            last->next = ptr;
            ptr->next = head;
        }

        printf("Member added successfully.\n");
    }
}

void removeMember() {
    char memberName[50];
    printf("Enter the name of the member to remove: ");
    scanf("%s", memberName);

    struct member *current = head;
    struct member *prev = NULL;

    if (head == NULL) {
        printf("List is empty. Cannot remove.\n");
        return;
    }

    // Find the member to remove
    while (strcmp(current->name, memberName) != 0) {
        if (current->next == head) {
            printf("Member not found.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    if (current == head) {
        // If the member to be removed is the head
        if (head->next == head) {
            // Only one member in the list
            free(head);
            head = NULL;
        } else {
            // Update the last member's next pointer
            struct member *last = head;
            while (last->next != head) {
                last = last->next;
            }
            last->next = head->next;

            // Move head to the next member
            struct member *temp = head;
            head = head->next;

            free(temp);
        }
    } else {
        // If the member to be removed is not the head
        prev->next = current->next;
        free(current);
    }

    printf("Member removed successfully.\n");
}

void displayMembers() {
    struct member *ptr = head;
    if (ptr == NULL) {
        printf("No members to display.\n");
    } else {
        printf("\n*********Members List*********\n");
        do {
            printf("Name: %s, Age: %d, Membership Type: %s\n", ptr->name, ptr->age, ptr->membershipType);
            ptr = ptr->next;
        } while (ptr != head);
    }
}

void searchMember() {
    char memberName[50];
    printf("Enter the name of the member to search: ");
    scanf("%s", memberName);

    struct member *current = head;
    int found = 0;

    if (head == NULL) {
        printf("List is empty. Cannot search.\n");
        return;
    }

    // Search for the member
    do {
        if (strcmp(current->name, memberName) == 0) {
            printf("Member found - Name: %s, Age: %d, Membership Type: %s\n", current->name, current->age, current->membershipType);
            found = 1;
            break;
        }
        current = current->next;
    } while (current != head);

    if (!found) {
        printf("Member not found.\n");
    }
}

void exitProgram() {
    struct member *current = head;
    struct member *next;

    if (head != NULL) {
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }

    printf("Memory freed. Exiting program.\n");
    exit(0);
}
void randomDelete() {
    int prevIndex, count = 0;
    printf("Enter the index of the previous member to delete: ");
    scanf("%d", &prevIndex);

    struct member *current = head;
    struct member *previous = NULL;

    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    // Find the previous member
    while (count != prevIndex) {
        if (current->next == head) {
            printf("Invalid index. No member after the specified index.\n");
            return;
        }
        previous = current;
        current = current->next;
        count++;
    }

    // Delete the member after the specified index
    struct member *toBeDeleted = current->next;
    current->next = toBeDeleted->next;

    if (toBeDeleted == head) {
        // If the member to be deleted is the head, move head to the next member
        head = head->next;
    }

    free(toBeDeleted);
    printf("Member after index %d deleted successfully.\n", prevIndex);
}

