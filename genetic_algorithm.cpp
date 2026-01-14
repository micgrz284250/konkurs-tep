//
// Created by micha-grzebielec on 14.01.2026.
//

#include "genetic_algorithm.h"

#include <iostream>
#include <ostream>

using namespace std;

genetic_algorithm::genetic_algorithm(const my_smart_pointer<evaluator> &eval, const my_smart_pointer<problem> &prb, int groups, int population_size, int round_count, double cross_prob, double mutation_prob) :
eval(eval),
prb(prb),
rng(random_device()()) {
    this->groups = groups;
    this->population_size = population_size;
    this->round_count = round_count;
    this->cross_prob = cross_prob;
    this->mutation_prob = mutation_prob;
    this->population.clear();
}

vector<int> genetic_algorithm::simulate() {
    // inicjalizacja każdego osobnika
    for (int i = 0; i < population_size; i++) {
        population.emplace_back(eval, prb->get_dimension(), groups);
        population[i].initialize_genotype();
    }

    // symulacja mutowania i krzyżowania
    for (int i = 0; i < round_count; i++) {

    }

    double best_fitness = INFINITY; // smaller fitness means better fitness
    vector<int> best_solution;
    for (int i = 0; i < population_size; i++) {
        double fitness = eval->evaluate(population[i].get_genotype_ref(), groups);
        cout << fitness << endl;
        if (fitness < best_fitness) {
            best_fitness = fitness;
            best_solution = population[i].get_genotype_ref();
        }
    }

    return best_solution;
}

void genetic_algorithm::cross(vector<individual>& pop) {
    uniform_int_distribution<int> distribution(0, pop.size() - 1);
    vector<individual> new_population;

    int individual_1 = distribution(rng);
    int individual_2 = distribution(rng);
    while (individual_1 == individual_2) individual_2 = distribution(rng);
    int parent_1 = individual_2;
    if (eval->evaluate(population[individual_1].get_genotype_ref(), groups) <= eval->evaluate(population[individual_2].get_genotype_ref(), groups)) parent_1 = individual_1;

    individual_1 = distribution(rng);
    individual_2 = distribution(rng);
    while (individual_1 == individual_2) individual_2 = distribution(rng);
    int parent_2 = individual_2;
    if (eval->evaluate(population[individual_1].get_genotype_ref(), groups) <= eval->evaluate(population[individual_2].get_genotype_ref(), groups)) parent_2 = individual_1;

    vector<individual> children = pop[parent_1].cross(pop[parent_2]);

    new_population.insert(new_population.end(), children.begin(), children.end());
}
