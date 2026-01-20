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
    optimization_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem>& prb) :
    eval(eval),
    prb(prb),
    rng(random_device()()) {
        this->groups = 0;
    }

    optimization_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem>& prb, int groups) :
    eval(eval),
    prb(prb),
    rng(random_device()()) {
        this->groups = groups;
    }

    virtual ~optimization_algorithm() = default;

    /// @brief Zwraca optymalny znaleziony wynik dla problemu.
    ///
    /// Do działania algorytm musi mieć przypisane:
    /// 1. implementację ewaluatora <evaluator> — oblicza jakość podanego osobnika
    /// 2. wybrany problem <problem> — problem, dla którego ma być dokonana optymalizacja
    ///
    /// @return vector<int> - wektor optymalnego rozwiązania
    [[nodiscard]] virtual vector<int> optimize() = 0;

    void set_evaluator(my_smart_pointer<evaluator> &value) {
        eval = my_smart_pointer(value);
    };

    void set_problem(my_smart_pointer<problem> &value) {
        prb = my_smart_pointer(value);
    };

    void set_groups(const int value) {
        this->groups = value;
    };
protected:
    my_smart_pointer<evaluator> eval;
    my_smart_pointer<problem> prb;
    mt19937 rng;

    int groups;
};


#endif //KONKURS_OPTIMIZATION_ALGORITHM_H