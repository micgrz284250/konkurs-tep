//
// Created by mkgrz on 08.01.2026.
//

#include "evaluator.hpp"

#include <cmath>
#include <iostream>

#include "../constants.hpp"

evaluator::evaluator(const my_smart_pointer<problem>& problem) : prb(problem) {
}

double evaluator::evaluate(const vector<int>& solution, const int groups) {
    double fitness = 0.0;

    if (solution.size() != prb->get_dimension()) return WRONG_SOLUTION_ERROR_CODE;

    int current_location_id = prb->get_depot();
    int goal_location_id;
    double distance;
    double group_demand = 0;

    for (int i = 0; i < groups; i++) {
        for (int j = 0; j < solution.size(); j++) {
            if (solution[j] == i) {
                goal_location_id = prb->get_permutation_ref()[j];
                distance = get_distance(current_location_id, goal_location_id);
                fitness += distance;
                current_location_id = goal_location_id;
                group_demand += prb->get_demands_ref()[current_location_id];

                if (group_demand > prb->get_capacity()) {
                    return INFINITY;
                }
            }
        }
        goal_location_id = prb->get_depot();
        distance = get_distance(current_location_id, goal_location_id);
        fitness += distance;
        group_demand = 0;
    }

    return fitness;
}

double evaluator::get_distance(const int client_1_id, const int client_2_id) {
    // cout << prb->get_edge_type() << endl;
    if (prb->get_edge_type() == "EUC_2D") {
        const tuple<double, double> client_1 = prb->get_coordinates_ref()[client_1_id];
        const tuple<double, double> client_2 = prb->get_coordinates_ref()[client_2_id];

        return sqrt(pow(get<0>(client_1) - get<0>(client_2), 2) + pow(get<1>(client_1) - get<1>(client_2), 2));
    }
    return WRONG_SOLUTION_ERROR_CODE;
}
