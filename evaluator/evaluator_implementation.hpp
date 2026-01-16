//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_EVALUATOR_IMPLEMENTATION_HPP
#define KONKURS_EVALUATOR_IMPLEMENTATION_HPP

#include <vector>

#include "evaluator.hpp"
#include "../problem.hpp"
#include "../smart_pointer/my_smart_pointer.hpp"

using namespace std;

class evaluator_implementation : evaluator {
public:
    explicit evaluator_implementation(const my_smart_pointer<problem>& problem);

    double evaluate(const vector<int>& solution, int groups);

    double get_distance(int client_1_id, int client_2_id);
};

#endif //KONKURS_EVALUATOR_IMPLEMENTATION_HPP