//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_EVALUATOR_IMPLEMENTATION_HPP
#define KONKURS_EVALUATOR_IMPLEMENTATION_HPP

#include <vector>

#include "evaluator.hpp"
#include "../problem/problem.hpp"
#include "../smart_pointer/my_smart_pointer.hpp"

using namespace std;

class evaluator_implementation : public evaluator {
public:
    double evaluate(vector<int>& solution, my_smart_pointer<problem>& prb, int groups) override;
};

#endif //KONKURS_EVALUATOR_IMPLEMENTATION_HPP