
#include "../unit_test/unit_test.h"

int main(void) {
    int res = unit_test();
    if (res) return res;
    printf("Unit Test Passed\n");
    return 0;
}