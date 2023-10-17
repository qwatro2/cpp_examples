#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    while (src_begin != src_end) {
        *dest++ = *src_begin++;
    }

    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    while (src_end != src_begin) {
        *(--dest) = *(--src_end);
    }
    return dest;
}