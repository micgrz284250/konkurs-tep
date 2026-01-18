//
// Created by micha-grzebielec on 14.01.2026.
//


#include <iostream>
#include <ostream>

#include "genetic_algorithm.hpp"
#include "../evaluator/evaluator_implementation.hpp"

using namespace std;

genetic_algorithm::genetic_algorithm(evaluator_implementation* evaluator, problem* problem) :
optimization_algorithm(evaluator, problem) {
    this->groups = 0;
    this->round_count = 0;
    this->population_count = 0;
    this->cross_prob = CROSS_PROB;
    this->mutation_prob = MUTATION_PROB;
}

genetic_algorithm::genetic_algorithm(evaluator_implementation *evaluator, problem *problem, const int groups, const int round_count, const int population_count, const double cross_prob, const double mutation_prob) :
optimization_algorithm(evaluator, problem) {
    this->groups = groups;
    this->round_count = round_count;
    this->population_count = population_count;
    this->cross_prob = cross_prob;
    this->mutation_prob = mutation_prob;
}

void genetic_algorithm::set_groups(const int value) {
    this->groups = value;
}

void genetic_algorithm::set_round_count(const int value) {
    this->round_count = value;
}

void genetic_algorithm::set_population_count(const int value) {
    this->population_count = value;
}

void genetic_algorithm::set_cross_prob(const double value) {
    this->cross_prob = value;
}

void genetic_algorithm::set_mutation_prob(const double value) {
    this->mutation_prob = value;
}

vector<int> genetic_algorithm::optimize(const int groups, const int population_size, const int round_count, const double cross_prob, const double mutation_prob) {
    vector<individual> population;

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

    // new_population.insert(new_population.end(), children.begin(), children.end());
}
