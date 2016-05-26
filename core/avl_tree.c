#include "avl_tree.h"


int max(int a, int b) { return a< b? b: a;}
int get_height(avl_pnode P ) {
    if (P==NULL) {
        return -1;
    }
    else
        return P->height;
}
avl_pnode single_rotate_with_left( avl_pnode k2 ) {
    avl_pnode k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(get_height(k2->left), get_height(k2->right)) + 1;
    k1->height = max(get_height(k1->left), get_height(k1->right)) + 1;
    return k1;
}
avl_pnode single_rotate_with_right( avl_pnode k1 ) {
    avl_pnode k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(get_height(k1->left), get_height(k1->right)) + 1;
    k2->height = max(get_height(k2->left), get_height(k2->right)) + 1;
    return k2;
}
avl_pnode double_rotate_with_left( avl_pnode k3 ) {
    //rotate between k1 and k2
    k3->left = single_rotate_with_right(k3->left);
    //rotate between k3 and k2
    return single_rotate_with_left(k3);
}
avl_pnode double_rotate_with_right( avl_pnode k3 ) {
    //rotate between k1 and k2
    k3->right = single_rotate_with_left(k3->right);
    //rotate between k3 and k2
    return single_rotate_with_right(k3);
}

AVL_Tree avl_insert( avl_element_t num, AVL_Tree avl_subtree ) {
    if (avl_subtree == NULL) {
        avl_subtree = (AVL_Tree)malloc(sizeof(AVL_Node));
        if (avl_subtree == NULL) {
            printf("FatalError : Out of space!!!\n");
            return NULL;
        }
        else {
            avl_subtree->element = num; avl_subtree->height = 0;
            avl_subtree->left = avl_subtree->right = NULL;
        }
    }
    else if (num < avl_subtree->element) {
        avl_subtree->left = avl_insert(num, avl_subtree->left);
        if (get_height(avl_subtree->left) - get_height(avl_subtree->right) == 2) {
            if ( num < avl_subtree->left->element)
                avl_subtree = single_rotate_with_left(avl_subtree);
            else
                avl_subtree = double_rotate_with_left(avl_subtree);
        }
    }
    else if(num > avl_subtree->element) {
        avl_subtree->right = avl_insert(num, avl_subtree->right);
        if (get_height(avl_subtree->right) - get_height(avl_subtree->left) == 2) {
            if (num > avl_subtree->right->element)
                avl_subtree = single_rotate_with_right(avl_subtree);
            else
                avl_subtree = double_rotate_with_right(avl_subtree);
        }
    }
    avl_subtree->height = max(get_height(avl_subtree->left), get_height(avl_subtree->right)) + 1;
    return avl_subtree;
}
void printInorder(AVL_Tree avl_subtree) {
    if (avl_subtree==NULL) return;
    printInorder(avl_subtree->left);
    printf("%d ", avl_subtree->element);
    printInorder(avl_subtree->right);
}
void avl_destroy(AVL_Tree avl_subtree) {
    if (avl_subtree== NULL) return;
    if (avl_subtree->left) {
        avl_destroy(avl_subtree->left);
    }
    if (avl_subtree->right) {
        avl_destroy(avl_subtree->right);
    }
    free(avl_subtree);
}
