#include <stdio.h>
#include <stdlib.h>

struct GymNode {
    int memberId;
    struct GymNode* left;
    struct GymNode* right;
};

struct GymNode* createGymNode(int memberId) {
    struct GymNode* newNode = (struct GymNode*)malloc(sizeof(struct GymNode));
    newNode->memberId = memberId;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void BFT(struct GymNode* root) {
    if (root == NULL) return;

    struct GymNode* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;

    while (front != rear) {
        struct GymNode* current = queue[++front];
        printf("%d ", current->memberId);

        if (current->left != NULL) queue[++rear] = current->left;
        if (current->right != NULL) queue[++rear] = current->right;
    }
}

void DFT(struct GymNode* root) {
    if (root == NULL) return;

    printf("%d ", root->memberId);

    DFT(root->left);
    DFT(root->right);
}

int searchBFT(struct GymNode* root, int target) {
    if (root == NULL) return 0;

    struct GymNode* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;

    while (front != rear) {
        struct GymNode* current = queue[++front];

        if (current->memberId == target) {
            return 1;
        }

        if (current->left != NULL) queue[++rear] = current->left;
        if (current->right != NULL) queue[++rear] = current->right;
    }

    return 0;
}

int searchDFT(struct GymNode* root, int target) {
    if (root == NULL) return 0;

    if (root->memberId == target) {
        return 1;
    }

    int leftSearch = searchDFT(root->left, target);
    int rightSearch = searchDFT(root->right, target);

    return leftSearch || rightSearch;
}

// Function to create Gym tree based on user input
struct GymNode* createGymTree() {
    int memberId;
    printf("Enter the root member ID: ");
    scanf("%d", &memberId);

    struct GymNode* root = createGymNode(memberId);

    printf("Enter the left child member ID for root %d (or -1 if none): ", memberId);
    scanf("%d", &memberId);
    if (memberId != -1) {
        root->left = createGymNode(memberId);
    }

    printf("Enter the right child member ID for root %d (or -1 if none): ", root->memberId);
    scanf("%d", &memberId);
    if (memberId != -1) {
        root->right = createGymNode(memberId);
    }

    // Allowing the user to input at least 5 elements
    for (int i = 0; i < 3; i++) {
        printf("Enter a member ID for an additional child (or -1 if none): ");
        scanf("%d", &memberId);

        if (memberId != -1) {
            // Create a new node and link it to the existing tree
            struct GymNode* newNode = createGymNode(memberId);
            struct GymNode* current = root;

            while (current->left != NULL && current->right != NULL) {
                current = current->left;
            }

            if (current->left == NULL) {
                current->left = newNode;
            } else {
                current->right = newNode;
            }
        }
    }

    return root;
}

int main() {
    struct GymNode* root = createGymTree();

    printf("Breadth-First Traversal (BFT): ");
    BFT(root);
    printf("\n");

    printf("Depth-First Traversal (DFT): ");
    DFT(root);
    printf("\n");

    int targetBFT;
    printf("Enter the member ID to search using BFT: ");
    scanf("%d", &targetBFT);
    if (searchBFT(root, targetBFT)) {
        printf("Member %d found in Gym using BFT.\n", targetBFT);
    } else {
        printf("Member %d not found in Gym using BFT.\n", targetBFT);
    }

    int targetDFT;
    printf("Enter the member ID to search using DFT: ");
    scanf("%d", &targetDFT);
    if (searchDFT(root, targetDFT)) {
        printf("Member %d found in Gym using DFT.\n", targetDFT);
    } else {
        printf("Member %d not found in Gym using DFT.\n", targetDFT);
    }

    return 0;
}
