#pragma once

#include <string>

template <class T>
class Counter {
public:
    explicit Counter(T* ptr) : ptr_(ptr), strong_count_(1), weak_count_(0) {
    }

    T* ptr_;
    int64_t strong_count_;
    int64_t weak_count_;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
    friend class WeakPtr<T>;

public:
    SharedPtr() : counter_(nullptr) {
    }

    explicit SharedPtr(T* ptr) : counter_(new Counter<T>(ptr)) {
    }

    SharedPtr(const SharedPtr& other) : counter_(other.counter_) {
        IncrementCounter();
    }

    SharedPtr(SharedPtr&& other) noexcept : counter_(other.counter_) {
        other.counter_ = nullptr;
    }

    explicit SharedPtr(const WeakPtr<T>& other) : counter_(other.counter_) {
        IncrementCounter();
    }

    ~SharedPtr() {
        DecrementCounter();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            DecrementCounter();
            counter_ = other.counter_;
            IncrementCounter();
        }

        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            DecrementCounter();
            counter_ = other.counter_;
            other.counter_ = nullptr;
        }

        return *this;
    }

    void Reset() {
        DecrementCounter();
        counter_ = nullptr;
    }

    void Reset(T* ptr) {
        DecrementCounter();
        counter_ = new Counter<T>(ptr);
    }

    T* Get() const {
        return counter_ ? counter_->ptr_ : nullptr;
    }

    explicit operator bool() const {
        return counter_ != nullptr;
    }

    T* operator->() const {
        return counter_->ptr_;
    }

    T& operator*() const {
        return *(counter_->ptr_);
    }

private:
    Counter<T>* counter_;

    void IncrementCounter() {
        if (counter_) {
            ++counter_->strong_count_;
        }
    }

    void DecrementCounter() {
        if (counter_) {
            --counter_->strong_count_;

            if (counter_->strong_count_ == 0) {
                if (counter_->weak_count_ == 0) {
                    delete counter_->ptr_;
                    delete counter_;
                } else {
                    delete counter_->ptr_;
                    counter_->ptr_ = nullptr;
                }
            }
        }
    }
};

template <class T>
class WeakPtr {
    friend class SharedPtr<T>;

public:
    WeakPtr() : counter_(nullptr) {
    }

    explicit WeakPtr(const SharedPtr<T>& shared_ptr) : counter_(shared_ptr.counter_) {
        IncrementCounter();
    }

    WeakPtr(const WeakPtr& other) : counter_(other.counter_) {
        IncrementCounter();
    }

    WeakPtr(WeakPtr&& other) noexcept : counter_(other.counter_) {
        other.counter_ = nullptr;
    }

    ~WeakPtr() {
        DecrementCounter();
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            DecrementCounter();
            counter_ = other.counter_;
            IncrementCounter();
        }

        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            DecrementCounter();
            counter_ = other.counter_;
            other.counter_ = nullptr;
        }

        return *this;
    }

    void Reset() {
        DecrementCounter();
        counter_ = nullptr;
    }

    SharedPtr<T> Lock() const {
        return SharedPtr<T>(*this);
    }

    bool IsExpired() const {
        return !counter_ || counter_->strong_count_ == 0;
    }

    explicit operator bool() const {
        return counter_ != nullptr;
    }

private:
    Counter<T>* counter_;

    void IncrementCounter() {
        if (counter_) {
            ++counter_->weak_count_;
        }
    }

    void DecrementCounter() {
        if (counter_) {
            --counter_->weak_count_;

            if (counter_->strong_count_ == 0 && counter_->weak_count_ == 0) {
                delete counter_;
            }
        }
    }
};
