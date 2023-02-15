#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod {
    int data;
    struct nod *left, *right;
} nod;

nod ROOT = {
    .data = 0,
    .left = NULL,
    .right = NULL
};

void inorder_tree_walk(nod *x) {
    if (x != NULL) {
        inorder_tree_walk(x->left);
        printf("%d -> ", x->data);
        inorder_tree_walk(x->right);
    }
}

int main() {
    
    return 0;
}