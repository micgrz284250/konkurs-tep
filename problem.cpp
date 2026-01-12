//
// Created by mkgrz on 10.01.2026.
//

#include "problem.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <bits/valarray_after.h>

#include "constants.h"

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

problem::problem(const string& file_path) {
    this->name = "";
    this->dimension = 0;
    this->edge_type = "";
    this->capacity = 0;
    this->permutation.clear();
    this->demands.clear();
    this->depot = 0;
    this->coordinates.clear();

    load_problem(file_path);
}

void problem::load_problem(const string& file_path) {
    ifstream problem_file(file_path);

    // todo dodać obsługę błędów
    if (!problem_file.is_open()) {
        cout << "problem file not found" << endl;
    }

    string line;
    while (getline(problem_file, line)) {
        if (!line.empty()) {
            if (line.find("NAME") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) {
                    this->name = line.substr(colon_pos + 1);
                }
            }
            else if (line.find("DIMENSION") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) {
                    this->dimension = stoi(line.substr(colon_pos + 1));
                }
            }
            else if (line.find("EDGE_WEIGHT_TYPE") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) {
                    this->edge_type = line.substr(colon_pos + 1);
                }
            }
            else if (line.find("CAPACITY") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) {
                    this->capacity = stoi(line.substr(colon_pos + 1));
                }
            }
            else if (line.find("PERMUTATION") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) {
                    string s_permutation = line.substr(colon_pos + 1);
                    stringstream ss(s_permutation);
                    int customer_id;
                    while (ss >> customer_id) {
                        this->permutation.push_back(customer_id);
                    }
                }
            }
            else if (line.find("DEMAND_SECTION") != string::npos) {
                for (int i = 0; i < this->dimension; ++i) {
                    getline(problem_file, line);
                    size_t space_pos = line.find(' ');
                    if (space_pos != string::npos) {
                        int customer_demand = stoi(line.substr(space_pos + 1));
                        this->demands.push_back(customer_demand);
                    }
                }
            }
            else if (line.find("DEPOT_SECTION") != string::npos) {
                getline(problem_file, line);
                this->depot = stoi(line);
            }
            else if (line.find("NODE_COORD_SECTION") != string::npos) {
                for (int i = 0; i < this->dimension; ++i) {
                    getline(problem_file, line);
                    size_t space_pos = line.find(' ');
                    string s_coordinates = line.substr(space_pos + 1);
                    space_pos = s_coordinates.find(' ');
                    double x = stod(s_coordinates.substr(0, space_pos));
                    double y = stod(s_coordinates.substr(space_pos + 1));
                    this->coordinates.emplace_back(x, y);
                }
            }
        }
    }
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

double problem::evaluate(const vector<int>& solution, int groups) const {
    double fitness = 0.0;

    if (solution.size() != dimension) return WRONG_SOLUTION_ERROR_CODE;

    int current_location_id = depot;
    int goal_location_id;
    double distance;
    double group_demand = 0;

    for (int i = 0; i < groups; ++i) {
        for (int j = 0; j < solution.size(); ++j) {
            if (solution[j] == i) {
                goal_location_id = solution[j];
                distance = get_distance(current_location_id, goal_location_id);
                fitness += distance;
                current_location_id = goal_location_id;
            }
        }
        goal_location_id = depot;
        distance = get_distance(current_location_id, goal_location_id);
        fitness += distance;
    }

    return fitness;
}

double problem::get_distance(int client_1_id, int client_2_id) const {
    if (edge_type == "EUC_2D") {
        tuple<double, double> client_1 = coordinates.at(client_1_id);
        tuple<double, double> client_2 = coordinates.at(client_2_id);

        return sqrt(pow(get<0>(client_1) - get<0>(client_2), 2) + pow(get<1>(client_1) - get<1>(client_2), 2));
    }
    return WRONG_SOLUTION_ERROR_CODE;
}
