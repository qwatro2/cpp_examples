#pragma once

template <class T>
class UniquePtr {
public:
    UniquePtr() : ptr_(nullptr) {
    }

    explicit UniquePtr(T* target) : ptr_(target) {
    }

    UniquePtr(const UniquePtr& copy) = delete;

    UniquePtr(UniquePtr&& move) {
        ptr_ = move.ptr_;
        move.ptr_ = nullptr;
    }

    ~UniquePtr() {
        delete ptr_;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& move) {
        delete ptr_;
        ptr_ = move.ptr_;
        move.ptr_ = nullptr;
        return *this;
    }

    T* operator->() {
        return ptr_;
    }

    void Reset(T* object = nullptr) {
        T* temp = ptr_;
        ptr_ = object;
        delete temp;
    }

private:
    T* ptr_;
};