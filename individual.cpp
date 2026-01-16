//
// Created by mkgrz on 08.01.2026.
//

#include "individual.hpp"

#include "constants.hpp"

using namespace std;

individual::individual(const my_smart_pointer<evaluator_implementation>& eval) : eval(eval), rng(random_device()()) {;
    this->genotype.clear();
    this->localizations = 0;
    this->groups = 0;
}

individual::individual(const my_smart_pointer<evaluator_implementation>& eval, int localizations, int groups) :
eval(eval),
rng(random_device()()) {
    this->genotype.clear();
    this->localizations = localizations;
    this->groups = groups;
}

individual::individual(const my_smart_pointer<evaluator_implementation>& eval, const vector<int>& genotype, const int localizations, const int groups) : eval(eval), rng(random_device()()) {
    this->genotype = genotype;
    this->localizations = localizations;
    this->groups = groups;
}

vector<int>& individual::get_genotype_ref() {
    return this->genotype;
}

void individual::set_genotype(const vector<int>& genotype) {
    this->genotype = genotype;
}

void individual::set_localizations(int localizations) {
    this->localizations = localizations;
}

void individual::set_groups(int groups) {
    this->groups = groups;
}

double individual::evaluate() {
    return eval->evaluate(genotype, groups);
}

void individual::mutate() {
    uniform_real_distribution<double> real_dist(0, 1);
    uniform_int_distribution<int> int_dist(0, groups-1);

    for (int& i : genotype) {
        if (real_dist(rng) <= MUTATION_PROB) {
            i = int_dist(rng);
        }
    }
}

vector<individual> individual::cross(individual &ind) {
    uniform_real_distribution<double> real_dist(0, 1);
    uniform_int_distribution<int> int_dist(0, localizations);

    if (real_dist(rng) <= CROSS_PROB) {
        int split_index = int_dist(rng);
        vector<int> genotype_1_a(get_genotype_ref().begin(), get_genotype_ref().begin() + split_index);
        vector<int> genotype_1_b(get_genotype_ref().begin() + split_index, get_genotype_ref().end());

        vector<int> genotype_2_a(ind.get_genotype_ref().begin(), ind.get_genotype_ref().begin() + split_index);
        vector<int> genotype_2_b(ind.get_genotype_ref().begin() + split_index, ind.get_genotype_ref().end());

        vector<int> genotype_cross_1;
        genotype_cross_1.insert(genotype_cross_1.end(), genotype_1_a.begin(), genotype_1_a.end());
        genotype_cross_1.insert(genotype_cross_1.end(), genotype_2_b.begin(), genotype_2_b.end());

        vector<int> genotype_cross_2;
        genotype_cross_2.insert(genotype_cross_2.end(), genotype_2_a.begin(), genotype_2_a.end());
        genotype_cross_2.insert(genotype_cross_2.end(), genotype_1_b.begin(), genotype_1_b.end());

        vector<individual> children;

        children.emplace_back(this->eval, genotype_cross_1, this->localizations, this->groups);
        children.emplace_back(this->eval, genotype_cross_2, this->localizations, this->groups);

        return children;
    }
    return {};
}

void individual::initialize_genotype() {
    uniform_int_distribution<int> int_dist(0, groups-1);
    this->genotype.clear();
    for (int i = 0; i < localizations; i++) {
        genotype.push_back(int_dist(rng));
    }
}