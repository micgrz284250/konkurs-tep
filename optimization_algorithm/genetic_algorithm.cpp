//
// Created by micha-grzebielec on 14.01.2026.
//


#include <iostream>

#include "genetic_algorithm.hpp"
#include "../evaluator/evaluator_implementation.hpp"

using namespace std;

genetic_algorithm::genetic_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem>& prb) :
optimization_algorithm(eval, prb) {
    this->groups = 0;
    this->round_count = 0;
    this->population_size = 0;
    this->cross_prob = CROSS_PROB;
    this->mutation_prob = MUTATION_PROB;
}

genetic_algorithm::genetic_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem>& prb, const int groups, const int round_count, const int population_size, const double cross_prob, const double mutation_prob) :
optimization_algorithm(eval, prb) {
    this->groups = groups;
    this->round_count = round_count;
    this->population_size = population_size;
    this->cross_prob = cross_prob;
    this->mutation_prob = mutation_prob;
}

void genetic_algorithm::set_round_count(const int value) {
    this->round_count = value;
}

void genetic_algorithm::set_population_size(const int value) {
    this->population_size = value;
}

void genetic_algorithm::set_cross_prob(const double value) {
    this->cross_prob = value;
}

void genetic_algorithm::set_mutation_prob(const double value) {
    this->mutation_prob = value;
}

vector<int> genetic_algorithm::optimize() {
    vector<individual> population;

    // inicjalizacja każdego osobnika
    for (int i = 0; i < population_size; i++) {
        population.emplace_back(prb->get_dimension(), groups);
        population[i].initialize_genotype();
    }

    // symulacja krzyżowania i mutowania
    for (int i = 0; i < round_count; i++) {
        // krzyżujemy
        vector<individual> new_population;
        while (new_population.size() < population_size) {
            vector<individual> children = cross(population);
            new_population.insert(new_population.end(), children.begin(), children.end());
        }
        population = new_population;

        // mutujemy
        for (individual& j : population) {
            j.mutate();
        }
    }

    //wybieramy najlepszego osobnika
    double best_fitness = INFINITY; // smaller fitness means better fitness
    vector<int> best_solution;
    for (int i = 0; i < population_size; i++) {
        if (!population[i].is_evaluated()) population[i].evaluate(eval, prb);
        if (population[i].get_fitness() < best_fitness) {
            best_fitness = population[i].get_fitness();
            best_solution = population[i].get_genotype_ref();
        }
    }

    return best_solution;
}

vector<individual> genetic_algorithm::cross(vector<individual>& population) {
    individual& parent_1 = get_parent_candidate_ref(population);
    individual& parent_2 = get_parent_candidate_ref(population);

    vector<individual> children = parent_1.cross(parent_2);

    return children;
}

individual& genetic_algorithm::get_parent_candidate_ref(vector<individual>& population) {
    uniform_int_distribution distribution(0,  static_cast<int>(population.size() - 1));

    const int individual_1 = distribution(rng);
    int individual_2 = distribution(rng);
    while (individual_1 == individual_2) individual_2 = distribution(rng);

    if (!population[individual_1].is_evaluated()) population[individual_1].evaluate(eval, prb);
    if (!population[individual_2].is_evaluated()) population[individual_2].evaluate(eval, prb);

    int parent;
    if (population[individual_1].get_fitness() >= population[individual_2].get_fitness()) parent = individual_1;
    else parent = individual_2;

    return population[parent];
}
