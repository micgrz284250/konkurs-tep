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
    genetic_algorithm(evaluator_implementation* evaluator, problem* problem);

    genetic_algorithm(evaluator_implementation* evaluator, problem* problem, int groups, int round_count, int population_count, double cross_prob = CROSS_PROB, double mutation_prob = MUTATION_PROB);

    void cross(vector<individual> &population);

    void set_groups(int value);

    void set_round_count(int value);

    void set_population_count(int value);

    void set_cross_prob(double value);

    void set_mutation_prob(double value);
private:
    int groups;
    int round_count;
    int population_count;
    double cross_prob;
    double mutation_prob;
};


#endif //KONKURS_GENETIC_ALGORITHM_H