//
// Created by mkgrz on 17.01.2026.
//

#ifndef KONKURS_OPTIMIZATION_ALGORITHM_H
#define KONKURS_OPTIMIZATION_ALGORITHM_H
#include <random>

#include "../evaluator/evaluator_implementation.hpp"
#include "../problem.hpp"
#include "../constants.hpp"

class optimization_algorithm {
public:
    optimization_algorithm(evaluator_implementation* evaluator, problem* problem, const int groups, const int population_size, const int round_count, double cross_prob = CROSS_PROB, double mutation_prob = MUTATION_PROB);

    virtual ~optimization_algorithm() = default;

    virtual vector<int> simulate() = 0;

protected:
    my_smart_pointer<evaluator_implementation> eval;
    my_smart_pointer<problem> prb;
    int groups;
    int population_size;
    int round_count;
    double cross_prob;
    double mutation_prob;
    mt19937 rng;
};


#endif //KONKURS_OPTIMIZATION_ALGORITHM_H