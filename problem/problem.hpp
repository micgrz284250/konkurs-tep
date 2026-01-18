//
// Created by mkgrz on 10.01.2026.
//

#ifndef KONKURS_PROBLEM_H
#define KONKURS_PROBLEM_H
#include <string>
#include <vector>

#include "../smart_pointer/my_smart_pointer.hpp"

using namespace std;

class problem {
public:
    virtual ~problem() = default;

    template <typename T>
    static my_smart_pointer<T> get_problem(const string& path);

    [[nodiscard]] string get_name() const;

    [[nodiscard]] int get_dimension() const;

    [[nodiscard]] string get_edge_type() const;

    [[nodiscard]] int get_capacity() const;

    vector<int>& get_permutation_ref();

    vector<int>& get_demands_ref();

    [[nodiscard]] int get_depot() const;

    vector<tuple<double, double>>& get_coordinates_ref();

protected:
    string name;
    int dimension;
    string edge_type;
    int capacity;
    vector<int> permutation;
    vector<int> demands;
    int depot;
    vector<tuple<double, double>> coordinates;

    problem();

    virtual void load_problem(const string& file_path) = 0;
};

#endif //KONKURS_PROBLEM_H