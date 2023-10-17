#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    while (begin < end && *begin != value) {
        ++begin;
    }

    if (begin < end) {
        for (auto i = begin + 1; i < end; ++i) {
            if (*i != value) {
                ++begin;
                *begin = *i;
            }
        }
    }
    return begin;
}
