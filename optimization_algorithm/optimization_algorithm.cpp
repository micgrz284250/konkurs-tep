//
// Created by mkgrz on 17.01.2026.
//

#include "optimization_algorithm.hpp"

optimization_algorithm::optimization_algorithm(evaluator_implementation *evaluator, problem *problem) :
eval(evaluator),
prb(problem),
rng(random_device()()) {
}

void optimization_algorithm::set_evaluator_implementation(evaluator_implementation *value) {
    eval = my_smart_pointer(value);
}

void optimization_algorithm::set_problem(problem *value) {
    prb = my_smart_pointer(value);
}