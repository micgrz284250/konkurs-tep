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
    prb(prb) {
        this->groups = 0;
        this->thread_count = 1;
    }

    optimization_algorithm(const my_smart_pointer<evaluator>& eval, const my_smart_pointer<problem>& prb, const int groups) :
    eval(eval),
    prb(prb) {
        this->groups = groups;
        this->thread_count = 1;
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

    void set_thread_count(const int value) {
        this->thread_count = value;
    }
protected:
    my_smart_pointer<evaluator> eval;
    my_smart_pointer<problem> prb;
    int thread_count;
    int groups;
};


#endif //KONKURS_OPTIMIZATION_ALGORITHM_H