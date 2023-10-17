#include "sum_digits.h"

int64_t SumOfDigits(int64_t number) {
    const int ten = 10;
    int64_t sum = 0;
    while (number) {
        sum += number % ten;
        number /= ten;
    }
    return sum;
}