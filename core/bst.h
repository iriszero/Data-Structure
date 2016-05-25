#pragma once

static const int ALLOCATION_FAIL = 14;
static const int DUPLICATE_VALUE = 15;

#include <stdlib.h>
#include "bst.h"
typedef int bst_element_t;
struct BST {
    bst_element_t value;
    struct BST *left;
    struct BST *right;
};
typedef struct BST BST;

//Insert a new node with the key value into the BST. If the key already exists in the BST, return an error code.
BST* bst_insert(BST *root, bst_element_t key);

//find the node contaning min value in the given subtree
BST* bst_find_min_node(BST *root);

//delete a node with the given key value from the given subtree
BST* bst_delete(BST *root, bst_element_t key);

//Find the node containing key in subtree
BST* bst_find_node(BST *root, bst_element_t key);

//Destroy BST by postorder traversal
void bst_destroy(BST *root);