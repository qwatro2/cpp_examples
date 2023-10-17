#include "factorization.h"

#include <cmath>

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> factorization;
    auto sqrt_x = static_cast<int64_t>(std::sqrt(x)) + 1;

    for (int64_t i = 2; i < sqrt_x; ++i) {
        if (x % i == 0) {
            int power_of_prime = 0;
            while (x % i == 0) {
                ++power_of_prime;
                x /= i;
            }
            factorization.emplace_back(i, power_of_prime);
        }
    }

    if (x != 1) {
        factorization.emplace_back(x, 1);
    }

    return factorization;
}
