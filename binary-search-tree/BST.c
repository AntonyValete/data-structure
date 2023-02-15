#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *left, *right;
} node;

node *create_new_node(int data) {
    node *dummy = (node *) malloc(sizeof(node));

    dummy->data = data;
    dummy->left = dummy->right = NULL;

    return dummy;
}

node *search_node(node *root, int key_value) {
    if (root == NULL || root->data == key_value)
        return root;

    if (root->data > key_value)
        return search_node(root->left, key_value);
    return search_node(root->right, key_value);
}

void error_handler(int error_code) {
    switch (error_code) {
        case 1:
            fprintf(stderr, "ERROR. THERE MUST NOT BE DUPLICATES\n\n");
            break;
    }
}


node *insert_node(node *tree, int data) {
    if (tree == NULL)
        return create_new_node(data);

    if (tree->data > data)
        tree->left = insert_node(tree->left, data);
    else if (tree->data < data)
        tree->right = insert_node(tree->right, data);
    else
        error_handler(1);

    return tree;
}

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