//
// Created by mkgrz on 17.01.2026.
//

#ifndef KONKURS_EUC_MATRIX_PROBLEM_HPP
#define KONKURS_EUC_MATRIX_PROBLEM_HPP
#include "problem.hpp"

using namespace std;

class euc_matrix_problem : public problem {
public:
    ~euc_matrix_problem() override = default;
    int load_problem(const string& path) override;
    double get_distance(int client_1_id, int client_2_id) override;
};


#endif //KONKURS_EUC_MATRIX_PROBLEM_HPP