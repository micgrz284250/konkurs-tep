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
    //populacja, na której operujemy
    vector<individual> population;
    // maszyna generująca do inicjalizacji nowych osobników
    mt19937 main_thread_mt19937{random_device()()};
    // inicjalizacja każdego osobnika
    for (int i = 0; i < population_size; i++) {
        population.emplace_back(prb->get_dimension()-1, groups);
        population[i].initialize_genotype(main_thread_mt19937);
    }

    // szykujemy wątki, rozmiary populacji jakię watek będzie tworzył oraz maszyny losujące dla każdego wątku
    vector<thread> threads;
    vector<int> thread_population_sizes;
    const int base_size = population_size / thread_count;
    const int base_rest = population_size % thread_count;
    for (int j = 0; j < thread_count; j++) {
        if (j < base_rest) thread_population_sizes.push_back(base_size + 1);
        else thread_population_sizes.push_back(base_size);
    }
    // obliczamy początkowe index dla każdego wątku
    vector<int> thread_begin_indexes;
    int curr_index = 0;
    for (int j = 0; j < thread_count; j++) {
        thread_begin_indexes.push_back(curr_index);
        curr_index += thread_population_sizes[j];
    }
    vector<mt19937> thread_mt19937;
    for (int j = 0; j < thread_count; j++) thread_mt19937.emplace_back(random_device()());
    // każdy wektor ma swojego najlepszego osobnika, na koniec wybierzemy najlepszego z najlepszych
    vector<individual> thread_best_solutions(thread_count);

    // symulacja krzyżowania i mutowania
    for (int i = 0; i < round_count; i++) {

        // tworzymy wektor nowej populacji i rezerwujemy dla niego rozmiar
        vector<individual> new_population(population_size);

        // krzyżujemy
        for (int j = 0; j < thread_count ; j++) {
            threads.emplace_back([&population, &new_population, &thread_best_solutions, &thread_mt19937, this](const int thread_id, const int thread_population_size, const int thread_begin_index){
                int generated_population = 0;
                double thread_best_fitness = INFINITY;
                while (generated_population < thread_population_size) {
                    vector<individual> children = cross(population, thread_mt19937[thread_id]);
                    for (auto &child : children) {
                        // od razu dokonujemy ewaluacji
                        // od razu dokonujemy mutacji
                        if (generated_population < thread_population_size) {
                            if (!child.is_evaluated()) child.evaluate(eval, prb);
                            if (child.get_fitness() < thread_best_fitness) {
                                thread_best_fitness = child.get_fitness();
                                thread_best_solutions[thread_id] = child;
                            }
                            child.mutate(thread_mt19937[thread_id]);
                            if (!child.is_evaluated()) child.evaluate(eval, prb);
                            if (child.get_fitness() < thread_best_fitness) {
                                thread_best_fitness = child.get_fitness();
                                thread_best_solutions[thread_id] = child;
                            }
                            new_population[thread_begin_index + generated_population] = child;
                            generated_population++;
                        }
                    }
                }
            }, j, thread_population_sizes[j], thread_begin_indexes[j]);
        }
        for (auto &thread : threads) if (thread.joinable()) thread.join();
        population = new_population;
        threads.clear();

        // while (new_population.size() < population_size) {
        //     vector<individual> children = cross(population);
        //     new_population.insert(new_population.end(), children.begin(), children.end());
        // }

        // population = new_population;

        // mutujemy
        // for (int j = 0; j < thread_count; j++) {
        //     threads.emplace_back([&population, &thread_mt19937](const int thread_id, const int thread_population_size){
        //         // size 4
        //         // then pop_size = 250
        //         // begin index = 0 (0 * 250)
        //         // end_index = 0 + 250
        //         const int begin_index = thread_id * thread_population_size;
        //         const int end_index = begin_index + thread_population_size;
        //         for (int k = begin_index; k < end_index; k++) {
        //             population[k].mutate(thread_mt19937[thread_id]);
        //         }
        //     }, j, thread_population_sizes[j]);
        // }
        // for (auto &thread : threads) if (thread.joinable()) thread.join();
        // threads.clear();
    }

    //wybieramy najlepszego osobnika
    double best_fitness = INFINITY; // smaller fitness means better fitness
    vector<int> best_solution;

    // vector<individual> thread_best_solutions(thread_count);
    // for (int j = 0; j < thread_count; j++) {
    //     threads.emplace_back([&population, &thread_best_solutions, this](const int thread_id, const int thread_population_size, const int thread_begin_index) {
    //         const int thread_end_index = thread_begin_index + thread_population_size;
    //         double thread_best_fitness = INFINITY;
    //         for (int i = thread_begin_index; i < thread_end_index; i++) {
    //             if (!population[i].is_evaluated()) population[i].evaluate(eval, prb);
    //             if (population[i].get_fitness() < thread_best_fitness) {
    //                 thread_best_fitness = population[i].get_fitness();
    //                 thread_best_solutions[thread_id] = population[i];
    //             }
    //         }
    //     }, j, thread_population_sizes[j], thread_begin_indexes[j]);
    // }
    // for (auto &thread : threads) if (thread.joinable()) thread.join();

    for (auto &solution : thread_best_solutions) {
        if (!solution.is_evaluated()) solution.evaluate(eval, prb);
        if (solution.get_fitness() < best_fitness) {
            best_fitness = solution.get_fitness();
            best_solution = solution.get_genotype_ref();
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
