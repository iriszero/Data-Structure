#pragma once
#include "linked_list.h"

int linked_list_init(LinkedListHeader linked_list) {
    if (linked_list->next) linked_list_destroy(linked_list);

    linked_list->next = (LinkedListpNode)malloc(sizeof(linked_list_node));
    if (linked_list->next== NULL) return ALLOCATION_FAIL;
    linked_list->next->next = NULL;
    return SUCCESS;
}

int linked_list_is_empty(LinkedListHeader linked_list) {
    return (linked_list->next == NULL);
}

int linked_list_delete_node(linked_list_element_t num, LinkedListHeader linked_list) {
    LinkedListpNode pos = linked_list_find_previous(num, linked_list);
    if (pos == NULL) return NOT_FOUND;
    if (pos->next = NULL) return COLLAPSED;
    LinkedListpNode post_next_next = pos->next->next;
    free(pos->next);
    pos->next = post_next_next;
    return SUCCESS;
}

LinkedListpNode linked_list_find_previous(linked_list_element_t num, LinkedListHeader linked_list) {

    LinkedListpNode pos = linked_list;
    while (pos->next != NULL) {
        if (pos->next->element == num) {
            return pos;
        }
        else {
            pos = pos->next;
        }
    }
    return NULL;    //cannot find the element
}
LinkedListpNode linked_list_find(linked_list_element_t num, LinkedListHeader linked_list) {
    LinkedListpNode pos = linked_list;

    //a special case for empty linked_list
    //prevent header->element(waste value) == num
    if (pos->next == NULL) return NULL;
    pos = pos->next;

    while (pos != NULL) {
        if (pos->element == num) {
            return pos;
        }
        else {
            pos = pos->next;
        }
    }
    return NULL;    //cannot find the element
}
int linked_list_insert(linked_list_element_t num, LinkedListpNode pos) { //pos could be header node
    LinkedListpNode pos_next = pos->next;
    pos->next = (LinkedListpNode)malloc(sizeof(struct linked_list_node));
    if (pos->next == NULL) return ALLOCATION_FAIL;
    pos->next->element = num;
    pos->next->next = pos_next;
    return SUCCESS;
}
void linked_list_destroy(LinkedListHeader linked_list) {
    if (linked_list->next != NULL) linked_list_destroy(linked_list->next);
    free(linked_list);
}
void linked_list_print_element(LinkedListHeader linked_list) {
    printf("== Print Linked List ==");
    LinkedListpNode pos = linked_list->next;
    while(pos) {
        printf("%d ", pos->element);
    }
    printf("\n");
    printf("== End of List ==\n");
}
