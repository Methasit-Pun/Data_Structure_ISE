#include <stdio.h>
#include <stdlib.h>

struct btree_node{
    int data;
    struct btree_node *left;
    struct btree_node *right;
    struct btree_node *parent;
};

// sum of all its elements

int sum_btree(struct btree_node *root){
    if (root == NULL){
        return 0;
    }
    return root->data + sum_btree(root->right) + sum_btree(root->left);
}

int main() {
    // Example usage
    // Construct a binary tree
    struct btree_node *root = malloc(sizeof(struct btree_node));
    root->data = 1;
    root->left = malloc(sizeof(struct btree_node));
    root->left->data = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = malloc(sizeof(struct btree_node));
    root->right->data = 3;
    root->right->left = NULL;
    root->right->right = NULL;
    root->parent = NULL;
    root->left->parent = root;
    root->right->parent = root;

    // Calculate the sum of all elements in the binary tree
    int sum = sum_btree(root);
    printf("Sum of all elements in the binary tree: %d\n", sum);

    // Free dynamically allocated memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

