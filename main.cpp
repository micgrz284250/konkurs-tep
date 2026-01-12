#include <iostream>

#include "evaluator.h"
#include "individual.h"
#include "problem.h"

int main() {
    const std::string path = "../data/lcvrp/Vrp-Set-A/A-n32-k5.lcvrp";
    problem prb(path);

    my_smart_pointer<evaluator> e(new evaluator());

    auto ind_1 = individual(e);
    auto ind_2 = individual(e);
    ind_1.set_localizations(4);
    ind_1.set_groups(2);
    ind_2.set_localizations(4);
    ind_2.set_groups(2);

    vector<int> genotype_1;
    vector<int> genotype_2;

    genotype_1.push_back(1);
    genotype_1.push_back(2);
    genotype_1.push_back(1);
    genotype_1.push_back(2);

    genotype_2.push_back(2);
    genotype_2.push_back(1);
    genotype_2.push_back(2);
    genotype_2.push_back(1);

    ind_1.set_genotype(genotype_1);
    ind_2.set_genotype(genotype_2);
    ind_1.cross(ind_2);

    return 0;
}
