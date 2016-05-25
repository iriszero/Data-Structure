#pragma once
#include <stdio.h>
const int SUCCESS = 0;
const int NOT_FOUND = 11;
const int COLLAPSED = 12;
const int ALLOCATION_FAIL = 13;
typedef int ll_element_t;
typedef struct LLNode LLNode;
typedef struct LLNode *LLpNode;
typedef LLpNode LLHeader;


struct LLNode
{
    ll_element_t   element;
    LLNode          next;
};

void ll_init(LLHeader ll);
int ll_is_empty(LLHeader ll);
void ll_delete_node(LLHeader ll, ll_element_t num);
LLpNode ll_find_previous(LLHeader ll, ll_element_t num);
LLpNode ll_find( LLHeader, ll_element_t num);
void ll_insert(LLpNode ll, ll_element_t num);
void ll_destroy(LLHeader ll);
void ll_print_element(LLHeader ll);
