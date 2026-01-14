//
// Created by micha-grzebielec on 14.01.2026.
//

#include "genetic_algorithm.h"

using namespace std;

genetic_algorithm::genetic_algorithm(const my_smart_pointer<evaluator> &eval, const my_smart_pointer<problem> &prb, int groups, int population_size, int round_count, double cross_prob, double mutation_prob) :
eval(eval),
prb(prb) {
    this->groups = groups;
    this->population_size = population_size;
    this->round_count = round_count;
    this->cross_prob = cross_prob;
    this->mutation_prob = mutation_prob;
}
