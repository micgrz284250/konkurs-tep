//
// Created by mkgrz on 17.01.2026.
//

#include "optimization_algorithm.hpp"

optimization_algorithm::optimization_algorithm(evaluator_implementation *evaluator, problem *prb) :
eval(evaluator),
prb(prb),
rng(random_device()()) {
    this->groups = 0;
}

void optimization_algorithm::set_evaluator_implementation(evaluator_implementation *value) {
    eval = my_smart_pointer(value);
}

void optimization_algorithm::set_problem(problem *value) {
    prb = my_smart_pointer(value);
}

void optimization_algorithm::set_groups(const int value) {
    this->groups = value;
}
