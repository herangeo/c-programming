#include <stdio.h>
#include <stdlib.h>

// Structure to represent a gym member
struct Member {
    char name[50];
    char membership_type[20];
};

// Node structure for the linked list
struct Node {
    struct Member data;
    struct Node* next;
};

// Queue structure
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize an empty queue
void initializeQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue a gym member
void enqueue(struct Queue* queue, struct Member member) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = member;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a gym member
struct Member dequeue(struct Queue* queue) {
    struct Member emptyMember = {"", ""};

    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return emptyMember;
    }

    struct Node* temp = queue->front;
    struct Member member = temp->data;

    if (queue->front == queue->rear) {
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }

    free(temp);
    return member;
}

// Function to get the front member of the queue
struct Member peek(struct Queue* queue) {
    struct Member emptyMember = {"", ""};

    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return emptyMember;
    }

    return queue->front->data;
}

// Function to display the menu
void displayMenu() {
    printf("\n----- Gym Management System -----\n");
    printf("1. Enqueue Member\n");
    printf("2. Dequeue Member\n");
    printf("3. Peek at Front Member\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Queue gymQueue;
    initializeQueue(&gymQueue);

    int choice;
    struct Member member;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter member name: ");
                scanf("%s", member.name);
                printf("Enter membership type: ");
                scanf("%s", member.membership_type);
                enqueue(&gymQueue, member);
                printf("Member enqueued successfully\n");
                break;

            case 2:
                member = dequeue(&gymQueue);
                if (strcmp(member.name, "") != 0) {
                    printf("Member dequeued: %s\n", member.name);
                }
                break;

            case 3:
                member = peek(&gymQueue);
                if (strcmp(member.name, "") != 0) {
                    printf("Front member: %s\n", member.name);
                }
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
