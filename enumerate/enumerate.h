#pragma once

#include <utility>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class T>
class EnumeratorRange {
public:
    explicit EnumeratorRange(const T& current) : current_(current), number_(0) {
    }

    EnumeratorRange& operator++() {
        ++current_;
        ++number_;
        return *this;
    }

    auto operator*() {
        return std::pair<int, typename T::reference>(number_, *current_);
    }

    bool operator!=(const EnumeratorRange& other) {
        return current_ != other.current_;
    }

private:
    T current_;
    int number_;
};

template <class T>
auto Enumerate(T& iter) {

    return IteratorRange(EnumeratorRange(iter.begin()), EnumeratorRange(iter.end()));
}