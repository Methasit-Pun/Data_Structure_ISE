#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct btree_node {

    int data;
    struct btree_node *left;
    struct btree_node *right;
};

// Depth First Search function to search for a node with a given value
struct btree_node *dfs(struct btree_node *root, int value) {
    if (root == NULL)
        return NULL;

    if (root->data == value)
        return root;

    struct btree_node *found_l = dfs(root->left, value);
    if (found_l != NULL)
        return found_l;
    else
        return dfs(root->right, value);
}

// Function to create a new binary tree node
struct btree_node *createNode(int value) {
    struct btree_node *newNode = (struct btree_node *)malloc(sizeof(struct btree_node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    // Creating a sample binary tree with 3 nodes depth
    struct btree_node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    root->left->left->left = createNode(8);
    root->left->left->right = createNode(9);

    int searchValue = 8;
    struct btree_node *result = dfs(root, searchValue);

    if (result != NULL)
        printf("Node with value %d found in the binary tree.\n", searchValue);
    else
        printf("Node with value %d not found in the binary tree.\n", searchValue);

    // Free allocated memory for the binary tree nodes

    return 0;
}
