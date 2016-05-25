#include "linked_list.h"

int ll_init(LLHeader ll) {
    if (ll->next) ll_destroy(ll);

    ll->next = (LLpNode)malloc(sizeof(ll_node));
    if (ll->next== NULL) return ALLOCATION_FAIL;
    ll->next->next = NULL;
    return SUCCESS;
}

int ll_is_empty(LLHeader ll) {
    return (ll->next == NULL);
}

int ll_delete_node(ll_element_t num, LLHeader ll) {
    LLpNode pos = ll_find_previous(num, ll);
    if (pos == NULL) return NOT_FOUND;
    if (pos->next = NULL) return COLLAPSED;
    LLpNode post_next_next = pos->next->next;
    free(pos->next);
    pos->next = post_next_next;
    return SUCCESS;
}

LLpNode ll_find_previous(ll_element_t num, LLHeader ll) {

    LLpNode pos = ll;
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
LLpNode ll_find(LLHeader ll, ll_element_t num) {
    LLpNode pos = ll;

    //a special case for empty ll
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
int ll_insert(LLpNode pos, ll_element_t num) { //pos could be header node
    LLpNode pos_next = pos->next;
    pos->next = (LLpNode)malloc(sizeof(struct ll_node));
    if (pos->next == NULL) return ALLOCATION_FAIL;
    pos->next->element = num;
    pos->next->next = pos_next;
    return SUCCESS;
}
void ll_destroy(LLHeader ll) {
    if (ll->next != NULL) ll_destroy(ll->next);
    free(ll);
}
void ll_print_element(LLHeader ll) {
    printf("== Print Linked List ==");
    LLpNode pos = ll->next;
    while(pos) {
        printf("%d ", pos->element);
    }
    printf("\n");
    printf("== End of List ==\n");
}
