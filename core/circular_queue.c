#include "circular_queue.h"

int cq_init(CircularQueue* cq, int size) {
    if (cq != NULL) cq_destroy(cq);
    cq = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (cq == NULL) return ALLOCATION_FAIL;
    cq->key = (cq_element_t*) malloc(sizeof(cq_element_t) * size);
    cq->first = 1;
    cq->rear = 0;
    cq->cnt= 0;
    cq->capacity = size;
    return SUCCESS;

}
int cq_is_empty(CircularQueue* cq) {
    assert(cq);
    return cq->cnt == 0;
}
int cq_is_full(CircularQueue* cq) {
    assert(cq);
    return cq->capacity == cq->cnt;
}
int cq_pop(CircularQueue* cq) {
    assert(cq);
    if (cq_is_empty(cq)) {
        return EMPTY;
    }
    else {
        cq->first = (cq->first + 1) % (cq->capacity);
        cq->cnt--;
    }
    return SUCCESS;
}
int cq_push(CircularQueue* cq, cq_element_t num) {
    assert(cq);
    if (cq_is_full(cq)) {
        return FULL;
    }
    else {
        cq->cnt++;
        cq->rear = (cq->rear + 1) % (cq->capacity);
        cq->key[cq->rear] = num;
    }
    return SUCCESS;
}
cq_element_t cq_front (CircularQueue* cq) {
    if (cq_is_empty(cq)) {
        return NULL;
    }
    else {
        return cq->key[cq->first];
    }
}

cq_element_t cq_rear (CircularQueue* cq) {
    if (cq_is_empty(cq)) {
        return NULL;
    }
    else {
        return cq->key[cq->rear];
    }
}
void cq_destroy(CircularQueue* cq ) {
    free(cq->key);
    free(cq);
}