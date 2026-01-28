//
// Created by mkgrz on 17.01.2026.
//

#include "euc_matrix_problem.hpp"
#include "../constants.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int euc_matrix_problem::load_problem(const string& path) {
    ifstream problem_file(path);

    if (!problem_file.is_open()) {
        return FILE_NOT_FOUND_ERROR_CODE;
    }

    string line;
    while (getline(problem_file, line)) {
        if (!line.empty()) {
            if (line.find("NAME") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) this->name = line.substr(colon_pos + 1);
            }
            else if (line.find("DIMENSION") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) this->dimension = stoi(line.substr(colon_pos + 1));
            }
            else if (line.find("EDGE_WEIGHT_TYPE") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) this->edge_type = line.substr(colon_pos + 2);
            }
            else if (line.find("CAPACITY") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) this->capacity = stoi(line.substr(colon_pos + 1));
            }
            else if (line.find("PERMUTATION") != string::npos) {
                size_t colon_pos = line.find(':');
                if (colon_pos != string::npos) {
                    string s_permutation = line.substr(colon_pos + 1);
                    stringstream ss(s_permutation);
                    int customer_id;
                    while (ss >> customer_id) this->permutation.push_back(customer_id);
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

    if (name == SECTION_NOT_LOADED_STRING || edge_type == SECTION_NOT_LOADED_STRING) return FILE_LOAD_PROBLEM;
    if (dimension == SECTION_NOT_LOADED_INT || capacity == SECTION_NOT_LOADED_INT || depot == SECTION_NOT_LOADED_INT) return FILE_LOAD_PROBLEM;
    if (permutation.size() != dimension - 1) return FILE_LOAD_PROBLEM;
    if (demands.size() != dimension - 1) return FILE_LOAD_PROBLEM;
    if (coordinates.size() != dimension) return FILE_LOAD_PROBLEM;

    return FILE_LOADED_SUCCESSFULLY;
}

double euc_matrix_problem::get_distance(const int client_1_id, const int client_2_id) {
    if (client_1_id < 0 || client_1_id >= get_coordinates_ref().size()) throw invalid_argument("Client_1_id out of bounds");
    if (client_2_id < 0 || client_2_id >= get_coordinates_ref().size()) throw invalid_argument("Client_2_id out of bounds");

    const tuple<double, double> client_1 = get_coordinates_ref()[client_1_id];
    const tuple<double, double> client_2 = get_coordinates_ref()[client_2_id];

    return sqrt(pow(get<0>(client_1) - get<0>(client_2), 2) + pow(get<1>(client_1) - get<1>(client_2), 2));
}
