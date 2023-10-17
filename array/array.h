#pragma once

#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array() : size_(0), data_(nullptr) {
    }

    explicit Array(size_t size) : size_(size), data_(size == 0 ? nullptr : new T[size]) {
    }

    Array(std::initializer_list<T> list) : size_(list.size()), data_(nullptr) {
        if (size_ != 0) {
            data_ = new T[size_];
            for (auto i = 0; i < size_; ++i) {
                data_[i] = *(list.begin() + i);
            }
        }
    }

    Array(const Array& other) : size_(other.size()), data_(nullptr) {
        if (size_ != 0) {
            data_ = new T[size_];
            for (auto i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            size_ = other.size_;
            delete[] data_;
            data_ = new T[size_];
            for (auto i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    ~Array() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t size() const {  // NOLINT
        return size_;
    }

    class Iterator {
    public:
        explicit Iterator(T* current) : current_(current) {
        }

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        T& operator*() {
            return *current_;
        }

        bool operator!=(const Iterator& other) {
            return current_ != other.current_;
        }

    private:
        T* current_;
    };

    Iterator begin() const {  // NOLINT
        return Iterator(data_);
    }

    Iterator end() const {  // NOLINT
        return Iterator(data_ + size_);
    }
};
