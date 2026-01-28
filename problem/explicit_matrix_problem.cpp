//
// Created by micha-grzebielec on 28.01.2026.
//

#include "explicit_matrix_problem.hpp"

#include <cstring>
#include <fstream>
#include <regex>

explicit_matrix_problem::explicit_matrix_problem() {
    this->distance_matrix.clear();
}

int explicit_matrix_problem::load_problem(const string& path) {
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
            else if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
                for (int i = 0; i < this->dimension - 1; ++i) {
                    getline(problem_file, line);
                    distance_matrix.emplace_back();
                    stringstream ss(line);
                    double distance;
                    while (ss >> distance) {
                        this->distance_matrix[i].push_back(distance);
                    }
                }
            }
        }
    }

    if (name == SECTION_NOT_LOADED_STRING || edge_type == SECTION_NOT_LOADED_STRING) return FILE_LOAD_PROBLEM;
    if (dimension == SECTION_NOT_LOADED_INT || capacity == SECTION_NOT_LOADED_INT || depot == SECTION_NOT_LOADED_INT) return FILE_LOAD_PROBLEM;
    if (permutation.size() != dimension - 1) return FILE_LOAD_PROBLEM;
    if (demands.size() != dimension) return FILE_LOAD_PROBLEM;
    if (distance_matrix.size() != dimension - 1) return FILE_LOAD_PROBLEM;

    return FILE_LOADED_SUCCESSFULLY;
}

double explicit_matrix_problem::get_distance(int client_1_id, int client_2_id) {
    client_1_id--;
    client_2_id--;
    if (client_1_id == client_2_id) return 0;
    if (client_1_id > client_2_id) {
        return distance_matrix[client_1_id][client_2_id];
    }
    return distance_matrix[client_2_id][client_1_id];
}
