//
// Created by micha-grzebielec on 13.12.2025.
//

#ifndef TEP_5_REF_COUNTER_H
#define TEP_5_REF_COUNTER_H

class ref_counter {
public:
    ref_counter() {
        counter = 0;
    }

    int add() {
        return ++counter;
    }

    int dec() {
        return --counter;
    }

    int get() const {
        return counter;
    }

private:
    int counter;
};

#endif //TEP_5_REF_COUNTER_H