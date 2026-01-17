//
// Created by mkgrz on 17.01.2026.
//

#include "optimization_algorithm.hpp"

optimization_algorithm::optimization_algorithm(evaluator_implementation *evaluator, problem *problem, const int groups, const int population_size, const int round_count, const double cross_prob, const double mutation_prob) :
eval(evaluator),
prb(problem),
rng(random_device()()) {
    this->groups = groups;
    this->population_size = population_size;
    this->round_count = round_count;
    this->cross_prob = cross_prob;
    this->mutation_prob = mutation_prob;
}
