#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {

    if (n == 0) {
        return 0;
    }

    int64_t a = 0;
    int64_t b = 1;
    int64_t tmp = 0;
    for (int i = 0; i < n - 1; ++i) {
        tmp = b;
        b = a + b;
        a = tmp;
    }

    return b;
}
