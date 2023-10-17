#include "password.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <numeric>

bool ValidatePassword(const std::string& password) {
    const int min_size = 8;
    const int max_size = 14;
    const char min_symbol = '!';
    const char max_symbol = '~';

    size_t length = password.length();

    if (length < min_size || length > max_size) {
        return false;
    }

    bool flags[] = {false, false, false, false};

    for (auto c : password) {
        if (c < min_symbol || c > max_symbol) {
            return false;
        } else if (isupper(c)) {
            flags[0] = true;
        } else if (islower(c)) {
            flags[1] = true;
        } else if (isdigit(c)) {
            flags[2] = true;
        } else {
            flags[3] = true;
        }
    }

    int count_flags = std::reduce(flags, flags + 4, 0);

    return count_flags >= 3;
}
