//
// Created by mkgrz on 10.01.2026.
//

#include "../problem/problem.hpp"

#include <fstream>
#include <memory>

using namespace std;

problem::problem() {
    this->name = "";
    this->dimension = 0;
    this->edge_type = "";
    this->capacity = 0;
    this->permutation.clear();
    this->demands.clear();
    this->depot = 0;
    this->coordinates.clear();
}

template<typename T>
my_smart_pointer<T> problem::get_problem(const string& file_path) {
    auto prb = my_smart_pointer<T>(new T());
    prb->load_problem(file_path);
    return prb;
}

string problem::get_name() const {
    return name;
}

int problem::get_dimension() const {
    return dimension;
}

string problem::get_edge_type() const {
    return edge_type;
}

int problem::get_capacity() const {
    return capacity;
}

vector<int>& problem::get_permutation_ref() {
    return permutation;
}

vector<int>& problem::get_demands_ref() {
    return demands;
}

int problem::get_depot() const {
    return depot;
}

vector<tuple<double, double>>& problem::get_coordinates_ref() {
    return coordinates;
}
