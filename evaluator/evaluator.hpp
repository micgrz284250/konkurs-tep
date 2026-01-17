//
// Created by micha-grzebielec on 16.01.2026.
//

#ifndef KONKURS_EVALUATOR_HPP
#define KONKURS_EVALUATOR_HPP

#include "../problem/problem.hpp"
#include "../smart_pointer/my_smart_pointer.hpp"

using namespace std;

class evaluator {
public:
    explicit evaluator(const my_smart_pointer<problem>& problem);

    virtual double evaluate() = 0;

    virtual ~evaluator() = default;

protected:
    my_smart_pointer<problem> prb;
};


#endif //KONKURS_EVALUATOR_HPP