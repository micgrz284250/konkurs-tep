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
    virtual double evaluate(vector<int>& solution, my_smart_pointer<problem>& prb, int groups) = 0;

    virtual ~evaluator() = default;
};


#endif //KONKURS_EVALUATOR_HPP