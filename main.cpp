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

    constexpr int thread_count = 4;
    constexpr int groups = 2;
    constexpr int round_count = 10000;
    constexpr int population_size = 1000;

    genetic_algorithm ga(eval, prb, groups, round_count, population_size);
    ga.set_thread_count(thread_count);

    cout << "depot = " << "(" << get<0>(prb->get_coordinates_ref()[0]) << ", " << get<1>(prb->get_coordinates_ref()[0]) << ")" << endl;
    for (int i = 0; i < prb->get_permutation_ref().size(); i++) {
        int k = prb->get_permutation_ref()[i];
        cout << prb->get_permutation_ref()[i] << ", " << "(" << get<0>(prb->get_coordinates_ref()[k - 1]) << ", " << get<1>(prb->get_coordinates_ref()[k - 1]) << ")" << endl;
    }

    for (int j = 0; j < 5; j++) {
        vector result = ga.optimize();

        for (int i = 0; i < result.size() - 1; i++) cout << result[i] << ",";
        cout << result[result.size() - 1] << endl;
    }
    return 0;
}