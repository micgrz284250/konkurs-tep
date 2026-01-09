//
// Created by mkgrz on 08.01.2026.
//

#include "individual.h"


individual::individual(evaluator &eval)
: eval(&eval),
dist_int(0, ) {
    this->genotype.clear();
    this->localizations = 0;
    this->groups = 0;
}

std::vector<int>& individual::get_genotype() {
    return this->genotype;
}

// void individual::mutate() {
//     for (int i = 0; i < this->genotype.size(); i++) {
//         double chance =
//     }
// }
