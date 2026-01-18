//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_INDIVIDUAL_H
#define KONKURS_INDIVIDUAL_H

#include <random>
#include <vector>

#include "evaluator/evaluator_implementation.hpp"
#include "smart_pointer/my_smart_pointer.hpp"

using namespace std;

class individual {
public:
    individual(int localizations, int groups);

    individual(const vector<int> &genotype, int localizations, int groups);

    vector<int>& get_genotype_ref();

    void set_genotype(const vector<int> &genotype_);

    [[nodiscard]] double get_fitness() const;

    void evaluate(my_smart_pointer<evaluator_implementation>& eval);

    void mutate();

    vector<individual> cross(individual& ind);

    void initialize_genotype();
private:
    vector<int> genotype;
    int localizations;
    int groups;
    double fitness;
    bool evaluated;
    mt19937 rng;
};

#endif //KONKURS_INDIVIDUAL_H