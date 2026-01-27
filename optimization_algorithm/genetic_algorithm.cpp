//
// Created by micha-grzebielec on 14.01.2026.
//


#include <iostream>
#include <thread>

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
    mt19937 main_thread_mt19937{random_device()()};
    // inicjalizacja każdego osobnika
    for (int i = 0; i < population_size; i++) {
        population.emplace_back(prb->get_dimension()-1, groups);
        population[i].initialize_genotype(main_thread_mt19937);
    }

    constexpr int thread_count = 4;
    vector<thread> threads;

    vector<int> thread_population_sizes;
    const int base_size = population_size / thread_count;
    const int base_rest = population_size % thread_count;
    for (int j = 0; j < thread_count; j++) {
        if (j < base_rest) thread_population_sizes.push_back(base_size + 1);
        else thread_population_sizes.push_back(base_size);
    }

    vector<mt19937> thread_mt19937;
    for (int j = 0; j < thread_count; j++) thread_mt19937.emplace_back(random_device()());

    // symulacja krzyżowania i mutowania
    for (int i = 0; i < round_count; i++) {
        if (i % 1000 == 0) cout << i/1000 << endl;

        vector<vector<individual>> thread_population(thread_count);
        vector<individual> new_population;

        // krzyżujemy
        for (int j = 0; j < thread_count ; j++) {
            threads.emplace_back([&thread_population, &population, &thread_mt19937, this](const int thread_id, const int thread_population_size){
                while (thread_population[thread_id].size() < thread_population_size) {
                    vector<individual> children = cross(population, thread_mt19937[thread_id]);
                    thread_population[thread_id].insert(thread_population[thread_id].end(), children.begin(), children.end());
                }
                if (thread_population[thread_id].size() > thread_population_size) thread_population[thread_id].pop_back();
            }, j, thread_population_sizes[j]);
        }
        for (auto &thread : threads) if (thread.joinable()) thread.join();
        for (auto &thread_pop : thread_population) new_population.insert(new_population.end(), thread_pop.begin(), thread_pop.end());
        population = new_population;
        threads.clear();

        // while (new_population.size() < population_size) {
        //     vector<individual> children = cross(population);
        //     new_population.insert(new_population.end(), children.begin(), children.end());
        // }

        // population = new_population;

        // mutujemy
        for (int j = 0; j < thread_count; j++) {
            threads.emplace_back([&population, &thread_mt19937](const int thread_id, const int thread_population_size){
                // size 4
                // then pop_size = 250
                // begin index = 0 (0 * 250)
                // end_index = 0 + 250
                const int begin_index = thread_id * thread_population_size;
                const int end_index = begin_index + thread_population_size;
                for (int k = begin_index; k < end_index; k++) {
                    population[k].mutate(thread_mt19937[thread_id]);
                }
            }, j, thread_population_sizes[j]);
        }
        for (auto &thread : threads) if (thread.joinable()) thread.join();
        threads.clear();
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

    cout << eval->evaluate(best_solution, prb, groups) << endl;
    return best_solution;
}

vector<individual> genetic_algorithm::cross(vector<individual>& population, mt19937 &rng) {
    individual& parent_1 = get_parent_candidate_ref(population, rng);
    individual& parent_2 = get_parent_candidate_ref(population, rng);

    vector<individual> children = parent_1.cross(parent_2, rng);

    return children;
}

individual& genetic_algorithm::get_parent_candidate_ref(vector<individual> &population, mt19937 &rng) {
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
