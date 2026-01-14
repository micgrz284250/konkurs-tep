//
// Created by mkgrz on 08.01.2026.
//

#include "evaluator.h"

#include <cmath>

#include "constants.h"

evaluator::evaluator(my_smart_pointer<problem>& problem) : prb(problem) {
}

double evaluator::evaluate(const vector<int>& solution, int groups) const {
    double fitness = 0.0;

    if (solution.size() != prb->) return WRONG_SOLUTION_ERROR_CODE;

    int current_location_id = prb->get_depot();
    int goal_location_id;
    double distance;
    double group_demand = 0;

    for (int i = 0; i < groups; ++i) {
        for (int j : solution) {
            if (j == i) {
                goal_location_id = prb.get_permutation_ref()[i];
                distance = get_distance(current_location_id, goal_location_id, prb);
                fitness += distance;
                current_location_id = goal_location_id;
                group_demand += prb.get_demands_ref()[current_location_id];

                if (group_demand > prb.get_capacity()) {
                    return INFINITY;
                }
            }
        }
        goal_location_id = prb.get_depot();
        distance = get_distance(current_location_id, goal_location_id, prb);
        fitness += distance;
        group_demand = 0;
    }

    return fitness;
}

double evaluator::get_distance(int client_1_id, int client_2_id, problem& prb) const {
    if (prb.get_edge_type() == "EUC_2D") {
        const tuple<double, double> client_1 = prb.get_coordinates_ref()[client_1_id];
        const tuple<double, double> client_2 = prb.get_coordinates_ref()[client_2_id];

        return sqrt(pow(get<0>(client_1) - get<0>(client_2), 2) + pow(get<1>(client_1) - get<1>(client_2), 2));
    }
    return WRONG_SOLUTION_ERROR_CODE;
}
