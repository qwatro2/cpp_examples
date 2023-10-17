#include "min_divisor.h"

#include <cmath>

int64_t MinDivisor(int64_t number) {
    int sqrt_number = static_cast<int>(std::sqrt(number)) + 1;
    for (int i = 2; i < sqrt_number; ++i) {
        if (number % i == 0) {
            return i;
        }
    }

    return number;
}
