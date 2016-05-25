#include <stdlib.h>
#include "bst.h"

/*Insert a new node with the key value into the BST.
 If the key already exists in the BST or there is a duplicative value already, return NULL; */
BST* bst_insert(BST *root, bst_element_t key) {
    if (root == NULL) {
        root = (BST*)malloc(sizeof(BST));
        if (root == NULL) {
            return root; // ALLOCATION_FAIL
        }
        else {
            root->value = key;
            root->left = root->right = NULL;
            return root; // Normal Execution
        }
    }
    else {
        if (root->value > key) {
            root->left = bst_insert(root->left, key);
        }
        else if (root->value < key) {
            root->right = bst_insert(root->right, key);
        }
        else {
            return NULL; //Duplicative Value
        }
    }
    return root;
}

BST* bst_find_min(BST *root) {
    if (root == NULL) {
        return NULL;
    }
    else if(root->left == NULL) {
        return root;
    }
    else {
        return bst_find_min(root->left);
    }
}

//delete a node with the given key value from the BST.
BST* bst_delete(BST *root, bst_element_t key) {
    if (root==NULL) {
        //not existing
        return root;
    }
    else if (root->value > key) {
        root->left = bst_delete(root->left, key);
    }
    else if (root->value < key) {
        root->right = bst_delete(root->right, key);
    }
    else if (root->left != NULL && root->right != NULL) {
        BST *ret = bst_find_min(root->right);
        root->value = ret->value;
        root->right = bst_delete(root->right, root->value);
    }
    else {
        BST *tmp = root;
        if (tmp->left == NULL) {
            root = root->right;
        }
        else if(tmp->right == NULL) {
            root = root->right;
        }
        free(root);
    }
    return root;
}

//Find the node containing key in BST
BST* bst_find_node(BST *root, bst_element_t key) {
    if (root == NULL) return NULL; //could not find the key
    if (root->value == key) return root;
    else if (root->value > key) return bst_find_node(root->left, key);
    else return bst_find_node(root->right, key);
}

//Destroy BST by postorder traversal
void bst_destroy(BST *root) {
    if (root->left) {
        bst_destroy(root->left);
    }
    if (root->right) {
        bst_destroy(root->right);
    }
    free(root);
}