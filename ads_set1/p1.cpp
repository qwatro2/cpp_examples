#include <stdexcept>
#include <vector>
#include <unordered_set>

struct Node {
    Node* next;
    Node* previous;
    int data;
    
    Node() : next(nullptr), previous(nullptr), data(0) { }
    Node(int value) : next(nullptr), previous(nullptr), data(value) { }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) { }

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size_(0) {
        auto cur = other.head;

        while (cur) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }

    DoublyLinkedList(std::vector<int>& array) : head(nullptr), tail(nullptr), size_(0) {
        for (const auto i: array) {
            pushBack(i);
        }
    }

    ~DoublyLinkedList() {
        erase();
    }
    
    void pushBack(int data) {
        auto new_node = new Node(data);

        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            new_node->previous = tail;
            tail = new_node;
        }

        ++size_;
    }
    
    void pushFront(int data) {
        auto new_node = new Node(data);

        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->previous = new_node;
            head = new_node;
        }
        
        ++size_;
    }

    void insert(Node* prev, int data) {
        if (prev && prev == tail) {
            pushBack(data);
            return;
        }

        if (!prev || !find_node(prev)) {
            throw std::runtime_error("Wrong position for insertion!");
        }

        auto new_node = new Node(data);
        new_node->previous = prev;
        new_node->next = prev->next;

        prev->next->previous = new_node;
        prev->next = new_node;

    	++size_;
    }

    void popFront() {
        if (size_ == 0) {
            throw std::runtime_error("Deletion error!");
        }

        auto old_head = head;
        head = head->next;

        if (head) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        
        delete old_head;

        --size_;
    }

    void popBack() {
        if (size_ == 0) {
            throw std::runtime_error("Deletion error!");
        }

        auto old_tail = tail;
        tail = tail->previous;

        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete old_tail;

        --size_;
    }

    void pop(Node* pos) {
        if (pos == head) {
            popFront();
            return;
        }
        
        if (pos == tail) {
            popBack();
            return;
        }

        if (!pos || !find_node(pos)) {
            throw std::runtime_error("Wrong position for deletion!");
        }

        pos->previous->next = pos->next;
        pos->next->previous = pos->previous;
        delete pos;

        --size_;
    }

    void erase() {
        while (size_ != 0) {
            popBack();
        }
    }

    void reverse() {
        if (size_ == 1) {
            std::swap(head, tail);
            return;
        }

        auto old_head = head;
        auto old_tail = tail;
        auto cur = head;

        while (cur) {
            std::swap(cur->previous, cur->next);
            cur = cur->previous;
        }

        head = old_tail;
        tail = old_head;
    }

    void removeDuplicates() {
        if (size_ == 1) {
            return;
        }

        Node* prev = nullptr;
        auto cur = head;
        std::unordered_set<int> set;

        while (cur) {
            if (set.find(cur->data) != set.end()) {
                safe_pop(cur);
            } else {
                set.insert(cur->data);
                prev = cur;
            }

            cur = prev->next;
        }
    }

    void replace(int oldElem, int newElem) {
        auto cur = head;

        while (cur) {
            if (cur->data == oldElem) {
                cur->data = newElem;
            }

            cur = cur->next;
        }
    }

private:
    size_t size_;

    bool find_node(Node* node) {
        if (size_ == 0) {
            return false;
        }

        if (size_ == 1) {
            return head == node;
        }

        auto cur = head;

        while (cur) {
            if (cur == node) {
                return true;
            }
            cur = cur->next;
        }

        return false;
    }

    void safe_pop(Node* pos) {
        if (size_ == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            pos->previous->next = pos->next;
            pos->next->previous = pos->previous;
            delete pos;
        }

        --size_;
    }
};