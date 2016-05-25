#pragma once
#include <stdlib.h>
#include <assert.h>

typedef int cq_element_t;
static const int SUCCESS = 0;
static const int EMPTY = 10;
static const int FULL = 11;
static const int ALLOCATION_FAIL = 14;
struct CircularQueue {
    cq_element_t *key;
    int first;
    int rear;
    int cnt;
    int capacity;
};

typedef struct CircularQueue CircularQueue;
int cq_init( CircularQueue* cq, int size );
int cq_is_empty( CircularQueue* cq );
int cq_is_full( CircularQueue* cq );
int cq_push( CircularQueue* cq , cq_element_t num);
int cq_pop( CircularQueue* cq );
cq_element_t cq_front (CircularQueue* cq);
cq_element_t cq_rear (CircularQueue* cq);
void cq_destroy (CircularQueue* cq );