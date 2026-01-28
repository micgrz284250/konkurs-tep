//
// Created by mkgrz on 08.01.2026.
//

#include "evaluator_implementation.hpp"

#include <cmath>
#include <iostream>

double evaluator_implementation::evaluate(vector<int>& solution, my_smart_pointer<problem>& prb, const int groups) {
    double fitness = 0.0;

    if (groups <= 0) throw invalid_argument("Groups below 1 exception");
    if (solution.size() != prb->get_permutation_ref().size()) throw invalid_argument("Wrong solution size");

    int current_location_id = prb->get_depot()-1;
    int goal_location_id;
    double distance;
    double group_demand = 0;

    for (int i = 0; i < groups; i++) {
        for (int j = 0; j < solution.size(); j++) {
            if (solution[j] == i) {
                goal_location_id = prb->get_permutation_ref()[j]-1;
                distance = prb->get_distance(current_location_id, goal_location_id);
                fitness += distance;
                current_location_id = goal_location_id;
                group_demand += prb->get_demands_ref()[current_location_id];

                if (group_demand > prb->get_capacity()) {
                    return INFINITY;
                }
            }
        }
        goal_location_id = prb->get_depot()-1;
        distance = prb->get_distance(current_location_id, goal_location_id);
        fitness += distance;
        current_location_id = goal_location_id;
        group_demand = 0;
    }

    return fitness;
}
