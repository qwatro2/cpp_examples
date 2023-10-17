#pragma once

#include <stddef.h>

#include <iostream>
#include <utility>

template <typename T>
class List {
private:
    struct ListNode {
        T value;
        ListNode* next;
        ListNode* prev;
    };

    void Clear() {
        auto cur = front_;
        while (cur != back_) {
            ListNode* next = cur->next;
            delete cur;
            cur = next;
        }
        delete cur;
    }

    ListNode* front_;
    ListNode* back_;
    size_t size_;

public:
    class Iterator {
    public:
        explicit Iterator(ListNode* node) : node_(node), prev_(nullptr) {
            if (node_ != nullptr) {
                prev_ = node_->prev;
            }
        }

        Iterator(ListNode* node, ListNode* prev) : node_(node), prev_(prev) {
        }

        Iterator& operator++() {
            if (node_ != nullptr) {
                prev_ = node_;
                node_ = node_->next;
            }

            return *this;
        }

        Iterator operator++(int) {
            auto current_state = node_;

            if (node_ != nullptr) {
                prev_ = node_;
                node_ = node_->next;
            }

            return Iterator(current_state);
        }

        Iterator& operator--() {
            if (node_ != nullptr) {
                node_ = node_->prev;
            } else {
                node_ = prev_;
            }

            if (node_ != nullptr) {
                prev_ = node_->prev;
            }

            return *this;
        }

        Iterator operator--(int) {
            auto cur = node_;

            if (node_ != nullptr) {
                node_ = node_->prev;
            } else {
                node_ = prev_;
            }

            if (node_ != nullptr) {
                prev_ = node_->prev;
            }

            return Iterator(cur);
        }

        T& operator*() const {
            return node_->value;
        }

        T* operator->() const {
            return node_->value;
        }

        bool operator==(const Iterator& rhs) const {
            return node_ == rhs.node_;
        }

        bool operator!=(const Iterator& rhs) const {
            return node_ != rhs.node_;
        }

    private:
        ListNode* node_;
        ListNode* prev_;
    };

    List() : front_(nullptr), back_(nullptr), size_(0) {
    }

    List(const List& other) : front_(nullptr), back_(nullptr), size_(0) {
        auto current_node = other.front_;

        for (auto i = 0; i < other.size_; ++i) {
            PushBack(current_node->value);
            current_node = current_node->next;
        }
    }

    List(List&& other) noexcept : front_(other.front_), back_(other.back_), size_(other.size_) {
        other.front_ = nullptr;
        other.back_ = nullptr;
        other.size_ = 0;
    }

    ~List() {
        Clear();
    }

    List& operator=(const List& other) {
        Clear();
        auto current_node = other.front_;

        for (auto i = 0; i < other.size_; ++i) {
            PushBack(current_node->value);
            current_node = current_node->next;
        }

        return *this;
    }

    List& operator=(List&& other) noexcept {
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;

        other.front_ = nullptr;
        other.back_ = nullptr;
        other.size_ = 0;

        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        auto new_back = new ListNode{elem, nullptr, back_};

        if (back_ != nullptr) {
            back_->next = new_back;
        } else {
            front_ = new_back;
        }

        back_ = new_back;
        ++size_;
    }

    void PushBack(T&& elem) {
        auto new_back = new ListNode{T(std::move(elem)), nullptr, back_};

        if (back_ != nullptr) {
            back_->next = new_back;
        } else {
            front_ = new_back;
        }

        back_ = new_back;
        ++size_;
    }

    void PushFront(const T& elem) {
        auto new_front = new ListNode{elem, front_, nullptr};

        if (front_ != nullptr) {
            front_->prev = new_front;
        } else {
            back_ = new_front;
        }

        front_ = new_front;
        ++size_;
    }

    void PushFront(T&& elem) {
        auto new_front = new ListNode{T(std::move(elem)), front_, nullptr};

        if (front_ != nullptr) {
            front_->prev = new_front;
        } else {
            back_ = new_front;
        }

        front_ = new_front;
        ++size_;
    }

    T& Front() {
        return front_->value;
    }

    const T& Front() const {
        return front_->value;
    }

    T& Back() {
        return back_->value;
    }

    const T& Back() const {
        return back_->value;
    }

    void PopBack() {
        if (back_ != nullptr) {
            auto prev_back = back_->prev;
            delete back_;
            back_ = prev_back;

            if (back_ == nullptr) {
                front_ = nullptr;
            } else {
                back_->next = nullptr;
            }

            --size_;
        }
    }

    void PopFront() {
        if (front_ != nullptr) {
            auto front_next = front_->next;
            delete front_;
            front_ = front_next;

            if (front_ == nullptr) {
                back_ = nullptr;
            } else {
                front_->prev = nullptr;
            }

            --size_;
        }
    }

    Iterator Begin() {
        return Iterator(front_);
    }

    Iterator End() {
        return back_ == nullptr ? Iterator(nullptr) : Iterator(back_->next, back_);
    }
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}