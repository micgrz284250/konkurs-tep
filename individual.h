//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_INDIVIDUAL_H
#define KONKURS_INDIVIDUAL_H

#include <random>
#include <vector>

#include "evaluator.h"
#include "smart_pointer/my_smart_pointer.h"

class individual {
public:
    explicit individual(evaluator& eval);

    std::vector<int>& get_genotype();

    double evaluate();

    void mutate();

    std::vector<individual> cross(const individual& ind);
private:
    std::vector<int> genotype;
    my_smart_pointer<evaluator> eval;

    int localizations;
    int groups;

    std::mt19937 rng;
};

#endif //KONKURS_INDIVIDUAL_H