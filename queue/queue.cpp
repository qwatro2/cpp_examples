#include "queue.h"

Node::Node(int32_t value, Node *next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    auto node = new Node(value, tail_);

    if (!Empty()) {
        tail_->next = node;
    }

    tail_ = node;
    if (Empty()) {
        front_ = node;
    }

    ++size_;
}

void Queue::Pop() {
    if (Empty()) {
        return;
    }

    auto current_front = front_;
    front_ = front_->next;
    delete current_front;

    if (front_ == nullptr) {
        tail_ = nullptr;
    }

    --size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (size_ > 0) {
        Pop();
    }
}

bool Queue::Empty() const {
    return size_ == 0;
}