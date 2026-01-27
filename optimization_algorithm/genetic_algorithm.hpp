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
    genetic_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem> &prb);

    genetic_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem> &prb, int groups, int round_count, int population_size, double cross_prob = CROSS_PROB, double mutation_prob = MUTATION_PROB);

    void set_round_count(int value);

    void set_population_size(int value);

    void set_cross_prob(double value);

    void set_mutation_prob(double value);

    vector<int> optimize() override;
private:
    int round_count;
    int population_size;
    double cross_prob;
    double mutation_prob;

    vector<individual> cross(vector<individual> &population, mt19937 &rng);

    individual& get_parent_candidate_ref(vector<individual>& population, mt19937 &rng);
};


#endif //KONKURS_GENETIC_ALGORITHM_H