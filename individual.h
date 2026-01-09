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
    std::mt19937 seed;
    std::uniform_int_distribution<int> dist_int;
    std::uniform_real_distribution<double> dist_double;
    int localizations;
    int groups;
};

#endif //KONKURS_INDIVIDUAL_H