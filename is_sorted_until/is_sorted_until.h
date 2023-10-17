#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    while (begin < end - 1) {
        if (*(begin + 1) < *begin) {
            return begin + 1;
        }
        ++begin;
    }
    return end;
}
