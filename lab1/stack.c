#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BinaryTree;

bool is_leaf(TreeNode* node) {
    return node == NULL || (node->left == NULL && node->right == NULL);
}

TreeNode* tree_node_init(int data) {
    TreeNode* new_node = malloc(sizeof(TreeNode));
    new_node->left = new_node->right = NULL;
    new_node->data = data;
    return new_node;
}

TreeNode** tree_find_node(BinaryTree* tree, int data, bool skip_existing) {
    TreeNode** current = &tree->root;
    while (*current != NULL) {
        if (data < (*current)->data) {
            current = &(*current)->left;
        }  else if (data > (*current)->data) {
            current = &(*current)->right;
        } else if (skip_existing) return NULL;
        else return current;
    }
    return current;
}

void tree_insert(BinaryTree* root, int data) {
    if (root->root == NULL) {
        root->root = tree_node_init(data);
        return;
    }
    TreeNode** node = tree_find_node(root, data, true);
    if (node != NULL && *node == NULL) {
        *node = tree_node_init(data);
    }
}

TreeNode** node_successor(TreeNode* node) {
    TreeNode** current = &node->right;
    while (*current != NULL && (*current)->left != NULL) {
        current = &(*current)->left;
    }
    return current;
}

void tree_pop(BinaryTree* root, int data) {
    TreeNode** node = tree_find_node(root, data, false);
    if (node == NULL || *node == NULL) return;
    if ((*node)->left == NULL && (*node)->right == NULL) {
        free(*node);
        *node = NULL;
    } else if ((*node)->left == NULL || (*node)->right == NULL) {
        // one child
        TreeNode* new_node;
        if ((*node)->left == NULL) new_node = (*node)->right;
        else new_node = (*node)->left;
        free(*node);
        *node = new_node;
    } else {
        // two children
        TreeNode** succ = node_successor(*node);
        (*node)->data = (*succ)->data;
        free(*succ);
        *succ = NULL;
    }
}

void tree_print(TreeNode* node) {
    if (node == NULL) return;
    tree_print(node->left);
    printf(" %d ", node->data);
    tree_print(node->right);
}

BinaryTree* tree_init() {
    BinaryTree* tree = malloc(sizeof(BinaryTree));
    return tree;
}


void node_destroy(TreeNode* node) {
    if (node == NULL) return;
    node_destroy(node->left);
    node_destroy(node->right);
    free(node);
}
void tree_destroy(BinaryTree* tree) {
    if (tree->root != NULL) {
        node_destroy(tree->root);
    }
    free(tree);
}

int main() {
    BinaryTree* tree = tree_init();
    tree_insert(tree, 10);
    tree_insert(tree, 5);
    tree_insert(tree, 5);
    tree_insert(tree, 12);
    tree_insert(tree, 11);
    tree_insert(tree, 13);
    tree_insert(tree, 4);
    tree_insert(tree, 6);
    tree_insert(tree, 8);
    tree_insert(tree, 7);
    tree_print(tree->root);
    tree_pop(tree, 10);
    printf("\n");
    tree_print(tree->root);
    tree_destroy(tree);
    return 0;
}