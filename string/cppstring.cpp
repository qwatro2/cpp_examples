#include "cppstring.h"

#include "cstring"

String::String() : size_(0), capacity_(0), data_(nullptr) {
}

String::String(size_t size, char symbol) : size_(size), capacity_(size) {
    if (size_ == 0) {
        data_ = nullptr;
        return;
    }

    data_ = new char[size_];
    for (auto i = 0; i < size_; ++i) {
        data_[i] = symbol;
    }
}

String::String(const char *src) : size_(strlen(src)), capacity_(strlen(src)), data_(nullptr) {
    if (size_ == 0) {
        return;
    }

    data_ = new char[size_];
    for (auto i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::String(const char *src, size_t size) : size_(size), capacity_(size), data_(nullptr) {
    if (size_ == 0) {
        return;
    }

    data_ = new char[size_];
    for (auto i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::~String() {
    Clear();
}

String::String(const String &other) : size_(other.Size()), capacity_(other.Capacity()) {
    if (this == &other) {
        return;
    }

    if (capacity_ == 0) {
        data_ = nullptr;
        return;
    }

    data_ = new char[capacity_];
    for (auto i = 0; i < size_; ++i) {
        data_[i] = other[i];
    }
}

String &String::operator=(const String &other) {
    if (this == &other) {
        return *this;
    }

    size_ = other.Size();
    capacity_ = other.Capacity();
    delete[] data_;
    data_ = size_ > 0 ? new char[capacity_] : nullptr;
    for (auto i = 0; i < size_; ++i) {
        data_[i] = other[i];
    }
    return *this;
}

const char &String::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }

    return *(data_ + idx);
}

char &String::operator[](size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }

    return *(data_ + idx);
}

const char &String::At(size_t idx) const {
    return (*this)[idx];
}

char &String::At(size_t idx) {
    return (*this)[idx];
}

const char &String::Front() const {
    if (Empty()) {
        throw StringOutOfRange();
    }

    return *data_;
}

char &String::Front() {
    if (Empty()) {
        throw StringOutOfRange();
    }

    return *data_;
}

const char &String::Back() const {
    if (Empty()) {
        throw StringOutOfRange();
    }

    return *(data_ + size_ - 1);
}

char &String::Back() {
    if (Empty()) {
        throw StringOutOfRange();
    }

    return *(data_ + size_ - 1);
}

const char *String::Data() const {
    return data_;
}

char *String::Data() {
    return data_;
}

const char *String::CStr() const {
    return data_;
}

char *String::CStr() {
    return data_;
}

bool String::Empty() const {
    return size_ == 0;
}

size_t String::Size() const {
    return size_;
}

size_t String::Length() const {
    return size_;
}

size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    if (data_) {
        delete[] data_;
    }
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void String::Swap(String &other) {
    std::swap(*this, other);
}

void String::PopBack() {
    if (size_ == 0) {
        return;
    }

    --size_;
}

void String::PushBack(char c) {
    if (capacity_ == 0) {
        delete[] data_;
        data_ = new char[]{c};
        capacity_ = 1;
        size_ = 1;
        return;
    }

    if (size_ == capacity_) {
        Reserve(capacity_ * 2);
    }

    ++size_;
    *(data_ + size_ - 1) = c;
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size > size_) {
        capacity_ = new_size * 2;

        if (data_ == nullptr) {
            data_ = new char[capacity_];
        } else {
            Reserve(capacity_);
        }

        for (auto i = size_; i < new_size; i++) {
            data_[i] = symbol;
        }

        size_ = new_size;
    } else {
        size_ = new_size;
    }
}

void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    auto new_data = new char[new_capacity];
    std::move(data_, data_ + size_, new_data);

    if (data_ != nullptr) {
        delete[] data_;
        data_ = nullptr;
    }

    data_ = new_data;
    capacity_ = new_capacity;

    if (new_capacity < capacity_) {
        size_ = new_capacity;
    }
}

void String::ShrinkToFit() {
    capacity_ = size_;

    auto new_data = new char[capacity_];
    std::move(data_, data_ + size_, new_data);

    if (data_ != nullptr) {
        delete[] data_;
        data_ = nullptr;
    }

    data_ = new_data;
}

int String::Compare(const String &other) const {
    if (size_ >= other.Size()) {
        for (auto i = 0; i < other.Size(); ++i) {
            if (At(i) < other[i]) {
                return 1;
            } else if (At(i) > other[i]) {
                return -1;
            }
        }

        return size_ == other.Size() ? 0 : -1;
    }

    for (auto i = 0; i < size_; ++i) {
        if (At(i) < other[i]) {
            return 1;
        } else if (At(i) > other[i]) {
            return -1;
        }
    }

    return 1;
}

String &String::operator+=(const String &other) {
    for (auto i = 0; i < other.Size(); ++i) {
        this->PushBack(other[i]);
    }
    return *this;
}

String operator+(const String &first, const String &second) {
    auto sum = String(first.Size() + second.Size(), ' ');

    auto first_size = first.Size();
    for (auto i = 0; i < first_size; ++i) {
        sum[i] = first[i];
    }
    for (auto i = 0; i < second.Size(); ++i) {
        sum[first_size + i] = second[i];
    }

    return sum;
}

std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (auto i = 0; i < string.Size(); ++i) {
        stream.put(string[i]);
    }

    return stream;
}

bool operator==(const String &first, const String &second) {
    if (first.Size() != second.Size()) {
        return false;
    }

    for (auto i = 0; i < first.Size(); ++i) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const String &first, const String &second) {
    return !(first == second);
}

bool operator>(const String &first, const String &second) {
    return first.Compare(second) < 0;
}

bool operator<(const String &first, const String &second) {
    return first.Compare(second) > 0;
}

bool operator>=(const String &first, const String &second) {
    return first.Compare(second) <= 0;
}

bool operator<=(const String &first, const String &second) {
    return first.Compare(second) >= 0;
}

void SafeCpy(char *dest, const char *src, size_t len) {
    for (auto i = 0; i < len; ++i) {
        *(dest + i) = *(src + i);
    }
}