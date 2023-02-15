#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *left, *right;
} node;

void inorder_tree_walk(node *root) {
    if (root != NULL) {
        inorder_tree_walk(root->left);
        printf("%d -> ", root->data);
        inorder_tree_walk(root->right);
    }
}

int main() {
    
    return 0;
}