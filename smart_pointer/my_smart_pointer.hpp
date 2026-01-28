//
// Created by micha-grzebielec on 13.12.2025.
//

#ifndef TEP_5_MY_SMART_POINTER_H
#define TEP_5_MY_SMART_POINTER_H

#include "../smart_pointer/ref_counter.hpp"

using namespace std;

template<typename T>
class my_smart_pointer {
    template<typename U> friend class my_smart_pointer;

public:
    explicit my_smart_pointer(T *ptr) {
        this->ptr = ptr;
        counter = new ref_counter();
        counter->add();
    }

    template <derived_from<T> U>
    my_smart_pointer(U *ptr) {
        this->ptr = ptr;
        counter = new ref_counter();
        counter->add();
    }

    my_smart_pointer(const my_smart_pointer &other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        counter->add();
    }

    template <derived_from<T> U>
    my_smart_pointer(const my_smart_pointer<U> &other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        counter->add();
    }

    my_smart_pointer(my_smart_pointer &&other) noexcept {
        this->ptr = other.ptr;
        this->counter = other.counter;
        other.ptr = nullptr;
        other.counter = nullptr;
    }

    ~my_smart_pointer() {
        if (counter != nullptr) {
            counter->dec();
            if (counter->get() == 0) {
                delete ptr;
                delete counter;
            }
        }
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    my_smart_pointer& operator=(const my_smart_pointer &other) {
        if (this == other) return *this;

        if (this->ptr != nullptr) {
            counter->dec();
            if (counter->get() == 0) {
                delete ptr;
                delete counter;
            }
        }

        this = my_smart_pointer(other);
        return *this;
    }

    my_smart_pointer& operator=(my_smart_pointer &&other) noexcept {
        if (this == &other) return *this;

        if (this->ptr != nullptr) {
            counter->dec();
            if (counter->get() == 0) {
                delete ptr;
                delete counter;
            }
        }

        this->ptr = other.ptr;
        this->counter = other.counter;
        other.ptr = nullptr;
        other.counter = nullptr;
        return *this;
    }
private:
    T *ptr;
    ref_counter *counter;
};

#endif //TEP_5_MY_SMART_POINTER_H