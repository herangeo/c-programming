#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key;
    char name[50];
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key, const char* name) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int key, const char* name) {
    if (root == NULL) {
        return createNode(key, name);
    }

    if (key < root->key) {
        root->left = insert(root->left, key, name);
    } else if (key > root->key) {
        root->right = insert(root->right, key, name);
    }

    return root;
}

void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Key: %d, Name: %s\n", root->key, root->name);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("Key: %d, Name: %s\n", root->key, root->name);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(struct Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("Key: %d, Name: %s\n", root->key, root->name);
    }
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        strcpy(root->name, temp->name);
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

int calculateHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void displayMenu() {
    printf("\nOptions:\n");
    printf("1. Add Member\n");
    printf("2. Delete Member\n");
    printf("3. Search Member\n");
    printf("4. In-order Traversal\n");
    printf("5. Pre-order Traversal\n");
    printf("6. Post-order Traversal\n");
    printf("7. Calculate Tree Height\n");
    printf("8. Exit\n");
}

int main() {
    struct Node* root = NULL;
    int option;

    do {
        displayMenu();
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter member key: ");
                int key;
                scanf("%d", &key);
                char name[50];
                printf("Enter member name: ");
                scanf("%s", name);
                root = insert(root, key, name);
                break;
            case 2:
                printf("Enter member key to delete: ");
                int deleteKey;
                scanf("%d", &deleteKey);
                root = deleteNode(root, deleteKey);
                break;
            case 3:
                printf("Enter member key to search: ");
                int searchKey;
                scanf("%d", &searchKey);
                struct Node* result = search(root, searchKey);
                if (result != NULL) {
                    printf("Member found. Key: %d, Name: %s\n", result->key, result->name);
                } else {
                    printf("Member not found.\n");
                }
                break;
            case 4:
                printf("In-order Traversal:\n");
                inOrderTraversal(root);
                break;
            case 5:
                printf("Pre-order Traversal:\n");
                preOrderTraversal(root);
                break;
            case 6:
                printf("Post-order Traversal:\n");
                postOrderTraversal(root);
                break;
            case 7:
                printf("Height of the BST: %d\n", calculateHeight(root));
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }

    } while (option != 8);


    return 0;
}
