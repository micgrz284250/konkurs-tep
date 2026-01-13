//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_EVALUATOR_H
#define KONKURS_EVALUATOR_H

#include <vector>

#include "problem.h"
#include "smart_pointer/my_smart_pointer.h"

using namespace std;

class evaluator {
public:
    evaluator(const my_smart_pointer<problem>& problem);

    double evaluate(const vector<int>& solution, int groups) const;

    double get_distance(int client_1_id, int client_2_id, problem& prb) const;

private:
    my_smart_pointer<problem> prb;
};


#endif //KONKURS_EVALUATOR_H