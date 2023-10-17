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
class RangeIterator {
public:
    explicit RangeIterator(const T& current, const T& step) : current_(current), step_(step) {
    }

    RangeIterator& operator++() {
        current_ += step_;
        return *this;
    }

    T operator*() {
        return current_;
    }

    bool operator!=(const RangeIterator& other) const {
        return current_ < other.current_;
    }

private:
    T current_;
    T step_;
};

template <class T>
auto Range(const T end) {
    return IteratorRange<RangeIterator<T>>(RangeIterator<T>(0, 1), RangeIterator<T>(end, 1));
}

template <class T>
auto Range(const T begin, const T end, const T step = 1) {
    return IteratorRange(RangeIterator(begin, step), RangeIterator(end, step));
}

template <class T1, class T2>
class ZipIterator {
public:
    explicit ZipIterator(const T1 first, const T2 second) : first_(first), second_(second) {
    }

    ZipIterator& operator++() {
        ++first_;
        ++second_;
        return *this;
    }

    auto operator*() {
        return std::make_pair(*first_, *second_);
    }

    bool operator!=(const ZipIterator& other) const {
        return other.first_ != first_ || other.second_ != second_;
    }

private:
    T1 first_;
    T2 second_;
};

template <class T1, class T2>
auto Zip(const T1& first, const T2& second) {
    return IteratorRange(ZipIterator(first.begin(), second.begin()), ZipIterator(first.end(), second.end()));
}

template <class T>
class GroupIterator {
public:
    explicit GroupIterator(const T it, const T end) : iterator_(it), end_(end) {
    }

    GroupIterator& operator++() {
        auto current = iterator_;
        ++current;

        while (current != end_ && *iterator_ == *current) {
            ++iterator_;
            ++current;
        }

        ++iterator_;
        return *this;
    }

    auto operator*() {
        auto current_1 = iterator_;
        auto current_2 = iterator_;
        ++current_2;
        while (current_2 != end_ && *current_1 == *current_2) {
            ++current_1;
            ++current_2;
        }
        ++current_1;
        return IteratorRange(iterator_, current_1);
    }

    bool operator!=(const GroupIterator& other) const {
        return other.iterator_ != iterator_;
    }

private:
    T iterator_;
    T end_;
};

template <class T>
auto Group(const T& iterator) {
    return IteratorRange(GroupIterator(iterator.begin(), iterator.end()),
                         GroupIterator(iterator.end(), iterator.end()));
}