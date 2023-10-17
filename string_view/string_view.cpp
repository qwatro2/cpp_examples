#include "string_view.h"

#include "algorithm"
#include "cstring"

StringView::StringView() : string_(nullptr), size_(0) {
}

StringView::StringView(const char *source) : string_(source), size_(strlen(source)) {
}

StringView::StringView(const char *cstyle, size_t length) : string_(cstyle), size_(length) {
}

char StringView::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringViewOutOfRange();
    }
    return *(string_ + idx);
}

char StringView::At(size_t idx) const {
    return (*this)[idx];
}

char StringView::Front() const {
    return *string_;
}

char StringView::Back() const {
    return *(string_ + size_ - 1);
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

const char *StringView::Data() const {
    return string_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

void StringView::Swap(StringView &other) {
    std::swap(*this, other);
}

void StringView::RemovePrefix(size_t prefix_size) {
    string_ += prefix_size;
    size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
    return StringView(string_ + pos, count);
}
