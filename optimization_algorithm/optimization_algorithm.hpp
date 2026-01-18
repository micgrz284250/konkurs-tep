//
// Created by mkgrz on 17.01.2026.
//

#ifndef KONKURS_OPTIMIZATION_ALGORITHM_H
#define KONKURS_OPTIMIZATION_ALGORITHM_H
#include <random>

#include "../evaluator/evaluator_implementation.hpp"
#include "../problem/problem.hpp"

class optimization_algorithm {
public:
    optimization_algorithm(evaluator_implementation* evaluator, problem* prb);

    virtual ~optimization_algorithm() = default;

    /// @brief Zwraca optymalny znaleziony wynik dla problemu.
    ///
    /// Do działania algorytm musi mieć przypisane:
    /// 1. implementację ewaluatora <evaluator> — oblicza jakość podanego osobnika
    /// 2. wybrany problem <problem> — problem, dla którego ma być dokonana optymalizacja
    ///
    /// @return vector<int> - wektor optymalnego rozwiązania
    virtual vector<int> optimize() = 0;

    void set_evaluator_implementation(evaluator_implementation* value);

    void set_problem(problem* value);
protected:
    my_smart_pointer<evaluator_implementation> eval;
    my_smart_pointer<problem> prb;
    mt19937 rng;
};


#endif //KONKURS_OPTIMIZATION_ALGORITHM_H