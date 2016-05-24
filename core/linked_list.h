#pragma once
const int SUCCESS = 0;
const int NOT_FOUND = 11;
const int COLLAPSED = 12;
const int ALLOCATION_FAIL = 13;
typedef int linked_list_element_t;
typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedListNode *LinkedListpNode;
typedef LinkedListpNode LinkedListHeader;


struct LinkedListNode
{
    linked_list_element_t   element;
    LinkedListNode          next;
};

void linked_list_init(LinkedListHeader linked_list);
int linked_list_is_empty(LinkedListHeader linked_list);
void linked_list_delete_node(linked_list_element_t num, LinkedListHeader linked_list);
LinkedListpNode linked_list_find_previous(linked_list_element_t num, LinkedListHeader linked_list);
LinkedListpNode linked_list_find(linked_list_element_t num, LinkedListHeader);
void linked_list_insert(linked_list_element_t num, LinkedListpNode linked_list);
void linked_list_destroy(LinkedListHeader linked_list);
void linked_list_print_element(LinkedListHeader linked_list);
