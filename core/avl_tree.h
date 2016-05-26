#pragma once
#include <stdlib.h>
#include <stdio.h>
typedef struct AVL_Node *avl_pnode;
typedef struct AVL_Node *AVL_Tree;
typedef int avl_element_t;
struct AVL_Node
{
    avl_element_t element;
    AVL_Tree left;
    AVL_Tree right;
    int height;
};
typedef struct AVL_Node AVL_Node;
int max(int a, int b);
int get_height(avl_pnode P );

//Following the 4 functions return the root that might be changed due to a rotation
avl_pnode single_rotate_with_left( avl_pnode k2 );
avl_pnode single_rotate_with_right( avl_pnode k1 );
avl_pnode double_rotate_with_left( avl_pnode k3 ) ;
avl_pnode double_rotate_with_right( avl_pnode k3 ) ;

AVL_Tree avl_insert( avl_element_t num, AVL_Tree avl_subtree ) ;
void printInorder(AVL_Tree avl_subtree) ;
void avl_destroy(AVL_Tree avl_subtree) ;