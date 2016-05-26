#include "random_generator.h"
int get_random_int(int min, int max) {
    assert(min <= max);
    int diff = max - min + 1, res;

    if (diff > RAND_MAX) {
        res = min + (diff / RAND_MAX) * get_random_int(0, RAND_MAX) + get_random_int(0, diff % RAND_MAX);
    }
    else {
        res = min + rand() % diff;
    }
    assert(min <= res && res <= max);
    return res;
}