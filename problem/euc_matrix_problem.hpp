//
// Created by mkgrz on 17.01.2026.
//

#ifndef KONKURS_EUC_MATRIX_PROBLEM_HPP
#define KONKURS_EUC_MATRIX_PROBLEM_HPP
#include "problem.hpp"

using namespace std;

class euc_matrix_problem : problem {
    void load_problem(const string& path) override;
};


#endif //KONKURS_EUC_MATRIX_PROBLEM_HPP