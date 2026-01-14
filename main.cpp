#include <iostream>

#include "evaluator.h"
#include "genetic_algorithm.h"
#include "problem.h"

int main() {
    const std::string path = "../data/lcvrp/Vrp-Set-A/A-n32-k5.lcvrp";
    my_smart_pointer<problem> prb(new problem(path));
    my_smart_pointer<evaluator> eval(new evaluator(prb));

    int groups = 10;
    int round_count = 10;
    int population_size = 10;

    genetic_algorithm ga(eval, prb, groups, population_size, round_count);
    ga.simulate();

    return 0;
}
