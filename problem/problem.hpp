//
// Created by mkgrz on 10.01.2026.
//

#ifndef KONKURS_PROBLEM_H
#define KONKURS_PROBLEM_H
#include <string>
#include <vector>

#include "../constants.hpp"
#include "../smart_pointer/my_smart_pointer.hpp"

using namespace std;

class problem {
public:
    virtual ~problem() = default;

    template <typename T>
    static my_smart_pointer<T> get_problem_pointer(const string &path) {
        auto prb = my_smart_pointer<T>(new T());
        const int error_code = prb->load_problem(path);
        if (error_code != FILE_LOADED_SUCCESSFULLY) {
            prb = my_smart_pointer<T>(nullptr);
        }
        return prb;
    }

    [[nodiscard]] string get_name() const {
        return name;
    }

    [[nodiscard]] int get_dimension() const {
        return dimension;
    }

    [[nodiscard]] string get_edge_type() const {
        return edge_type;
    }

    [[nodiscard]] int get_capacity() const {
        return capacity;
    }

    vector<int> &get_permutation_ref() {
        return permutation;
    }

    vector<int> &get_demands_ref() {
        return demands;
    }

    [[nodiscard]] int get_depot() const {
        return depot;
    }

    vector<tuple<double, double>> &get_coordinates_ref() {
        return coordinates;
    }

    virtual double get_distance(int client_1_id, int client_2_id) = 0;

    virtual int load_problem(const string& path) = 0;
protected:
    string name;
    int dimension;
    string edge_type;
    int capacity;
    vector<int> permutation;
    vector<int> demands;
    int depot;
    vector<tuple<double, double>> coordinates;

    problem() {
        this->name = SECTION_NOT_LOADED_STRING;
        this->edge_type = SECTION_NOT_LOADED_STRING;
        this->dimension = SECTION_NOT_LOADED_INT;
        this->capacity = SECTION_NOT_LOADED_INT;
        this->depot = SECTION_NOT_LOADED_INT;
        this->permutation.clear();
        this->demands.clear();
        this->coordinates.clear();
    }
};

#endif //KONKURS_PROBLEM_H