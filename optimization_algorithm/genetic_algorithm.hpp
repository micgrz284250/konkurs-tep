//
// Created by micha-grzebielec on 14.01.2026.
//

#ifndef KONKURS_GENETIC_ALGORITHM_H
#define KONKURS_GENETIC_ALGORITHM_H

#include "../optimization_algorithm/optimization_algorithm.hpp"
#include "../constants.hpp"
#include "../evaluator/evaluator_implementation.hpp"
#include "../individual.hpp"

using namespace std;

class genetic_algorithm : optimization_algorithm {
public:
    genetic_algorithm(evaluator_implementation* evaluator, problem* problem, const int groups, const int population_size, const int round_count, const double cross_prob = CROSS_PROB, const double mutation_prob = MUTATION_PROB);

    vector<int> simulate() override;

    void cross(vector<individual> &population);
};


#endif //KONKURS_GENETIC_ALGORITHM_H