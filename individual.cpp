//
// Created by mkgrz on 08.01.2026.
//

#include "individual.h"

individual::individual(evaluator &eval) {
    this->eval = &eval;
}

individual::~individual() {

}

std::vector<int>& individual::get_genotype() {
    return this->genotype;
}

void individual::mutate() {
    for (int i = 0; i < this->genotype.size(); i++) {
        double chance =
    }
}
