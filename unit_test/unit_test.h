#pragma once
#include "../core/rb_tree.h"
#include "random_generator.h"
#include <assert.h>

static const int MIN_TSIZE = 20;
static const int TEST_SUCCESS = 0;
static const int TEST_FAIL = 11;
int test_rbtree(int size);
int unit_test();