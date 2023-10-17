#include "hypotenuse.h"

#include <cmath>

double CalculateHypotenuse(int64_t a, int64_t b) {
    return std::sqrt(std::pow(a, 2) + std::pow(b, 2));
};
