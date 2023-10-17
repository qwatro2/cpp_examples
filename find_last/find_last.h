#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {

    if (first == last) {
        return last;
    }

    for (auto cur = last - 1; cur >= first; --cur) {
        if (*cur == val) {
            return cur;
        }
    }
    return last;
}
