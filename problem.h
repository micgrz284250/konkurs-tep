//
// Created by mkgrz on 10.01.2026.
//

#ifndef KONKURS_PROBLEM_H
#define KONKURS_PROBLEM_H
#include <string>
#include <vector>

using namespace std;

class problem {
public:
    explicit problem(const string& file_path);

    void load_problem(const string& file_path);

    string get_name() const;

    int get_dimension() const;

    string get_edge_type() const;

    int get_capacity() const;

    vector<int>& get_permutation_ref();

    vector<int>& get_demands_ref();

    int get_depot() const;

    vector<tuple<double, double>>& get_coordinates_ref();

private:
    string name;
    int dimension;
    string edge_type;
    int capacity;
    vector<int> permutation;
    vector<int> demands;
    int depot;
    vector<tuple<double, double>> coordinates;
};

#endif //KONKURS_PROBLEM_H