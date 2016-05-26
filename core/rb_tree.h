#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ELEMENT_MAX 2000

// DEFINE Circular QUEUE //
typedef enum Color { BLACK, RED } Color;
typedef int rbtree_element_type_t;
typedef struct rbnode rbnode;
typedef struct rbnode *ptr_rbnode;

typedef ptr_rbnode cq_element_t;

#define _DEFINE_CIRCULAR_QUEUE_
#include "circular_queue.h"

struct rbnode {
    rbtree_element_type_t val;
    ptr_rbnode left, right, parent;
    Color color;
    int nil;
};

//for debugging returns black_height
int assert_tree(ptr_rbnode node);

int is_leaf(ptr_rbnode node);
void delete_one_child(ptr_rbnode node);
void destroy_tree(ptr_rbnode root);
void make_balance_after_insert(ptr_rbnode node);
void rotate_left(ptr_rbnode node);
void rotate_right(ptr_rbnode node);

//for debugging
void print_space(int n);
void print_space(int n);
void print_preorder_with_tab(ptr_rbnode node, int depth);
void print_levelbylevel(ptr_rbnode root);

//following 9 functions return root that might be changed
ptr_rbnode delete_node(ptr_rbnode root, rbtree_element_type_t val, int logging);
ptr_rbnode find_node(ptr_rbnode node, rbtree_element_type_t val);
ptr_rbnode find_max_node(ptr_rbnode node) ;
ptr_rbnode get_grandparent(ptr_rbnode node);
ptr_rbnode get_uncle(ptr_rbnode node);
ptr_rbnode get_sibiling(ptr_rbnode node);
ptr_rbnode init_rbtree(void);
ptr_rbnode insert_node(ptr_rbnode root, rbtree_element_type_t val, int logging);
ptr_rbnode replace_node(ptr_rbnode root, ptr_rbnode src, ptr_rbnode dst);


