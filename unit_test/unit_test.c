#include "unit_test.h"


int test_rbtree(int size) {
    assert(size>= MIN_TSIZE);
    int i;
    ptr_rbnode root = init_rbtree();
    srand(time(NULL));
    for (i=0; i<size; i++) {
        int now = get_random_int(- size/8, size/8);
        int mode = get_random_int(0, 1);
        if (mode == 0) {
            //insert
            root = insert_node(root, now, 0);
        }
        else {
            //delete
            root = delete_node(root, now, 0);
        }
        assert_tree(root);
    }
    return TEST_SUCCESS;
}
int unit_test() {
    int res;
    res = test_rbtree(1000);
    if (res) return res;
    return TEST_SUCCESS;
}