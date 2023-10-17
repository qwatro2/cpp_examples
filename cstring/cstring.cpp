#include <cstddef>  // Для использования size_t

size_t Strlen(const char* str) {
    auto length = 0;

    while (*str != '\0') {
        ++length;
        ++str;
    }

    return length;
}

int Strcmp(const char* first, const char* second) {
    while (*first != '\0' && *first == *second) {
        ++first;
        ++second;
    }

    return static_cast<int>(*first) - static_cast<int>(*second);
}

int Strncmp(const char* first, const char* second, size_t count) {
    for (auto i = 0; i < count; ++i) {

        if (*first != *second) {
            return static_cast<int>(*first) - static_cast<int>(*second);
        }

        if (*first == '\0' || *second == '\0') {
            return 0;
        }

        ++first;
        ++second;
    }

    return 0;
}

char* Strcpy(char* dest, const char* src) {
    auto begin = dest;

    while (*src != '\0') {
        *dest = *src;
        ++dest;
        ++src;
    }

    *dest = '\0';

    return begin;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    auto begin = dest;

    for (auto i = 0; i < count; ++i) {
        if (*src != '\0') {
            *dest = *src;
            ++src;
        } else {
            *dest = '\0';
        }
        ++dest;
    }

    return begin;
}

char* Strcat(char* dest, const char* src) {
    auto begin = dest;

    while (*dest != '\0') {
        ++dest;
    }

    while (*src != '\0') {
        *dest = *src;
        ++dest;
        ++src;
    }

    *dest = '\0';

    return begin;
}

char* Strncat(char* dest, const char* src, size_t count) {
    auto begin = dest;

    while (*dest != '\0') {
        ++dest;
    }

    for (size_t i = 0; i < count; ++i) {
        if (*src != '\0') {
            *dest = *src;
            ++dest;
            ++src;
        } else {
            break;
        }
    }

    *dest = '\0';

    return begin;
}

const char* Strchr(const char* str, char symbol) {
    while (*str != '\0') {
        if (*str == symbol) {
            return str;
        }
        ++str;
    }

    if (symbol == '\0') {
        return str;
    }

    return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
    const char* last = nullptr;

    while (*str != '\0') {
        if (*str == symbol) {
            last = str;
        }
        ++str;
    }

    if (symbol == '\0') {
        return str;
    }

    return last;
}

size_t Strspn(const char* dest, const char* src) {
    auto count = 0;

    while (*dest != '\0' && Strchr(src, *dest) != nullptr) {
        ++count;
        ++dest;
    }

    return count;
}

size_t Strcspn(const char* dest, const char* src) {
    auto count = 0;

    while (*dest != '\0' && Strchr(src, *dest) == nullptr) {
        ++count;
        ++dest;
    }

    return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    while (*dest != '\0') {
        if (Strchr(breakset, *dest)) {
            return dest;
        }
        ++dest;
    }

    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return str;
    }

    while (*str != '\0') {
        const char* const_pattern = pattern;
        const char* const_str = str;

        while (*const_pattern != '\0' && *const_str == *const_pattern) {
            ++const_str;
            ++const_pattern;
        }

        if (*const_pattern == '\0') {
            return str;
        }

        ++str;
    }

    return nullptr;
}
