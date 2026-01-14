//
// Created by micha-grzebielec on 14.01.2026.
//

#ifndef KONKURS_GENETIC_ALGORITHM_H
#define KONKURS_GENETIC_ALGORITHM_H
#include "constants.h"
#include "evaluator.h"
#include "smart_pointer/my_smart_pointer.h"


class genetic_algorithm {
public:
    genetic_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem>& prb, int groups, int population_size, int round_count, double cross_prob = CROSS_PROB, double mutation_prob = MUTATION_PROB);

private:
    my_smart_pointer<evaluator> eval;
    my_smart_pointer<problem> prb;
    int groups;
    int population_size;
    int round_count;
    double cross_prob;
    double mutation_prob;
};


#endif //KONKURS_GENETIC_ALGORITHM_H