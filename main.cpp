#include <iostream>
#include <ostream>

#include "evaluator/evaluator_implementation.hpp"
#include "optimization_algorithm/genetic_algorithm.hpp"
#include "problem/euc_matrix_problem.hpp"
#include "problem/problem.hpp"

using namespace std;

int main() {
    const std::string path = "../data/lcvrp/Vrp-Set-P/P-n19-k2.lcvrp";
    my_smart_pointer<problem> prb = problem::get_problem<euc_matrix_problem>(path);
    my_smart_pointer<evaluator> eval(new evaluator_implementation());

    constexpr int groups = 2;
    constexpr int round_count = 10000;
    constexpr int population_size = 1000;

    genetic_algorithm ga(eval, prb, groups, round_count, population_size);
    vector result = ga.optimize();

    for (int i : result) {
        cout << i << ",";
    }

    return 0;
}
