//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_INDIVIDUAL_H
#define KONKURS_INDIVIDUAL_H

#include <random>
#include <vector>

#include "evaluator/evaluator.hpp"
#include "smart_pointer/my_smart_pointer.hpp"

using namespace std;

class individual {
public:
    explicit individual(const my_smart_pointer<evaluator>& eval);

    individual(const my_smart_pointer<evaluator>& eval, int localizations, int groups);

    individual(const my_smart_pointer<evaluator> &eval, const vector<int> &genotype, int localizations, int groups);

    vector<int>& get_genotype_ref();

    void set_genotype(const vector<int> &genotype);

    void set_localizations(int localizations);

    void set_groups(int groups);

    double evaluate();

    void mutate();

    vector<individual> cross(individual& ind);

    void initialize_genotype();
private:
    vector<int> genotype;
    my_smart_pointer<evaluator> eval;
    int localizations;
    int groups;
    mt19937 rng;
};

#endif //KONKURS_INDIVIDUAL_H