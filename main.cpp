#include "evaluator/evaluator_implementation.hpp"
#include "optimization_algorithm/genetic_algorithm.hpp"
#include "problem/euc_matrix_problem.hpp"
#include "problem/problem.hpp"

int main() {
    const std::string path = "../data/lcvrp/Vrp-Set-A/A-n32-k5.lcvrp";
    const my_smart_pointer<euc_matrix_problem> prb = problem::get_problem<euc_matrix_problem>(path);
    const my_smart_pointer eval(new evaluator_implementation());

    constexpr int groups = 10;
    constexpr int round_count = 10;
    constexpr int population_size = 10;

    genetic_algorithm ga(eval, prb, groups, round_count, population_size);

    return 0;
}
