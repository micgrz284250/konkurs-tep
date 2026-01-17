//
// Created by micha-grzebielec on 14.01.2026.
//

#ifndef KONKURS_GENETIC_ALGORITHM_H
#define KONKURS_GENETIC_ALGORITHM_H
#include "../constants.hpp"
#include "../evaluator/evaluator_implementation.hpp"
#include "../individual.hpp"
#include "../smart_pointer/my_smart_pointer.hpp"

using namespace std;

class genetic_algorithm {
public:
    genetic_algorithm(const my_smart_pointer<evaluator_implementation>& eval, const my_smart_pointer<problem>& prb, int groups, int population_size, int round_count, double cross_prob = CROSS_PROB, double mutation_prob = MUTATION_PROB);

    vector<int> simulate();

    void cross(vector<individual> &population);
private:
    my_smart_pointer<evaluator_implementation> eval;
    my_smart_pointer<problem> prb;
    vector<individual> population;
    int groups;
    int population_size;
    int round_count;
    double cross_prob;
    double mutation_prob;
    mt19937 rng;
};


#endif //KONKURS_GENETIC_ALGORITHM_H