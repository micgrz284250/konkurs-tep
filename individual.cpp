//
// Created by mkgrz on 08.01.2026.
//

#include "individual.h"

#include "constants.h"


individual::individual(evaluator &eval)
: eval(&eval), rng(std::random_device()()) {
    this->genotype.clear();
    this->localizations = 0;
    this->groups = 0;
}

std::vector<int>& individual::get_genotype() {
    return this->genotype;
}

void individual::mutate() {
    std::uniform_real_distribution<double> real_dist(0, 1);
    std::uniform_int_distribution<int> int_dist(0, groups);

    for (int& i : genotype) {
        if (real_dist(rng) <= mutation_prob) {
            i = int_dist(rng);
        }
    }
}