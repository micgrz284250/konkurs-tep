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
    problem();
    problem(const string& file_path);

    void load_problem(const string& file_path);
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