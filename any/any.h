#pragma once

#include "memory"

class Any {
private:
    struct InnerBase {
        virtual ~InnerBase() {
        }

        virtual InnerBase* Clone() const = 0;
    };

    template <class T>
    struct Inner : public InnerBase {
        T value;

        explicit Inner(const T& value) : value(value) {
        }

        InnerBase* Clone() const override {
            return new Inner<T>(value);
        }
    };

    InnerBase* ptr_ = nullptr;

public:
    Any();

    template <class T>
    explicit Any(const T& value) : ptr_(new Inner<T>(value)) {
    }

    template <class T>
    Any& operator=(const T& value) {
        delete ptr_;
        ptr_ = new Inner<T>(value);
        return *this;
    };

    Any(const Any& rhs);
    Any& operator=(Any rhs);
    ~Any();

    bool Empty() const;

    void Clear();
    void Swap(Any& rhs);

    template <class T>
    const T& GetValue() const {
        return dynamic_cast<Inner<T>&>(*ptr_).value;
    }
};