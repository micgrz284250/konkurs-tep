//
// Created by micha-grzebielec on 28.01.2026.
//

#ifndef KONKURS_EXPLICIT_MATRIX_PROBLEM_HPP
#define KONKURS_EXPLICIT_MATRIX_PROBLEM_HPP
#include "../optimization_algorithm/optimization_algorithm.hpp"


class explicit_matrix_problem : public problem {
    friend class problem;
public:
    ~explicit_matrix_problem() override = default;

    int load_problem(const string& path) override;

    double get_distance(int client_1_id, int client_2_id) override;
private:
    explicit_matrix_problem();

    vector<vector<double>> distance_matrix;
};


#endif //KONKURS_EXPLICIT_MATRIX_PROBLEM_HPP