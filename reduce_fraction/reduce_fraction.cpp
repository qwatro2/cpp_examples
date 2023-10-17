#include "reduce_fraction.h"

int64_t Gcd(int64_t a, int64_t b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a + b;
}

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t nod = Gcd(numerator, denominator);
    return (numerator + denominator) / nod;
}
