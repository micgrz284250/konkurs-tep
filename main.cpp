#include <iostream>
#include <ostream>

#include "evaluator/evaluator_implementation.hpp"
#include "optimization_algorithm/genetic_algorithm.hpp"
#include "problem/euc_matrix_problem.hpp"
#include "problem/problem.hpp"

using namespace std;

int main() {
    const std::string path = "../data/lcvrp/Vrp-Set-P/P-n19-k2.lcvrp";
    my_smart_pointer<problem> prb = problem::get_problem_pointer<euc_matrix_problem>(path);
    my_smart_pointer<evaluator> eval(new evaluator_implementation());

    constexpr int thread_count = 4;
    constexpr int groups = 2;
    constexpr int round_count = 10000;
    constexpr int population_size = 1000;

    my_smart_pointer<genetic_algorithm> op = optimization_algorithm::get_optimization_algorithm_pointer<genetic_algorithm>(eval, prb, groups);
    op->set_thread_count(thread_count);
    op->set_round_count(round_count);
    op->set_population_size(population_size);

    for (int j = 0; j < 5; j++) {
        vector result = op->optimize();

        for (int i = 0; i < result.size() - 1; i++) cout << result[i] << ",";
        cout << result[result.size() - 1] << endl;
    }
    return 0;
}