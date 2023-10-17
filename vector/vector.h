#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>

template <class T>
class Vector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void Realloc(size_t new_size) {
        if (data_ == nullptr) {
            data_ = new T[new_size];
            capacity_ = new_size;
            return;
        }
        auto new_data = new T[new_size];
        std::move(data_, data_ + size_, new_data);
        capacity_ = new_size;
        delete[] data_;
        data_ = new_data;
    }

public:
    Vector() {
        Reserve(1);
    }

    explicit Vector(size_t size) {
        Reserve(size);
        for (auto i = 0; i < size; ++i) {
            PushBack(0);
        }
    }

    Vector(std::initializer_list<T> list) {
        auto first = list.begin();
        auto last = list.end();

        Reserve(std::distance(first, last));

        while (first != last) {
            PushBack(*first);
            ++first;
        }
    }

    Vector(const Vector& rhs) {
        Reserve(rhs.Size());

        for (auto i = 0; i < rhs.Size(); ++i) {
            PushBack(rhs[i]);
        }
    }

    Vector(Vector&& rhs) : data_(rhs.Data()), size_(rhs.Size()), capacity_(rhs.Capacity()) {
        rhs.data_ = nullptr;
    }

    Vector& operator=(Vector rhs) {
        Swap(rhs);

        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(Vector& rhs) {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
    }

    void Reserve(size_t size) {
        if (size == 0) {
            size = 1;
        }
        if (size <= capacity_) {
            return;
        }

        Realloc(size);
    }

    void PushBack(T value) {
        if (size_ == capacity_) {
            Realloc(capacity_ * 2);
        }

        data_[size_++] = value;
    }

    void PopBack() {
        --size_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    T operator[](size_t index) const {
        return data_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    T* Data() const {
        return data_;
    }

    void Clear() {
        size_ = 0;
    }

    class Iterator {
    public:
        Iterator() {
        }

        explicit Iterator(T* current) : current_(current) {
        }

        Iterator& operator+=(ssize_t difference) {
            current_ += difference;
            return *this;
        }

        Iterator operator+(ssize_t difference) const {
            Iterator result(*this);
            result += difference;
            return result;
        }

        Iterator& operator-=(ssize_t difference) {
            current_ -= difference;
            return *this;
        }

        Iterator operator-(ssize_t difference) const {
            Iterator result(*this);
            result -= difference;
            return result;
        }

        Iterator& operator++() {
            *this += 1;
            return *this;
        }

        Iterator operator++(int) {
            Iterator result(*this);
            ++(*this);
            return result;
        }

        Iterator& operator--() {
            *this -= 1;
            return *this;
        }

        Iterator operator--(int) {
            Iterator result(*this);
            --(*this);
            return result;
        }

        bool operator==(const Iterator& rhs) const {
            return current_ == rhs.current_;
        }

        bool operator!=(const Iterator& rhs) const {
            return current_ != rhs.current_;
        }

        T& operator*() {
            return *current_;
        }

        T* operator->() {
            return current_;
        }

        size_t operator-(const Iterator& other) const {
            return current_ - other.current_;
        }

    private:
        T* current_;
    };

    Iterator begin() {  // NOLINT
        return Iterator(data_);
    }

    Iterator end() {  // NOLINT
        return Iterator(data_ + size_);
    }

    Iterator Begin() {
        return begin();
    }

    Iterator End() {
        return end();
    }
};