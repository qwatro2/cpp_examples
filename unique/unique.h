#pragma once

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return begin;
    }

    auto current_end = begin;
    while (++begin < end) {
        if (*current_end != *begin && ++current_end != begin) {
            *current_end = *begin;
        }
    }

    return ++current_end;
}