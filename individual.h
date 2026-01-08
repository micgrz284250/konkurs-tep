//
// Created by mkgrz on 08.01.2026.
//

#ifndef KONKURS_INDIVIDUAL_H
#define KONKURS_INDIVIDUAL_H

#include <vector>

class individual {
public:
    individual();

    std::vector<int> get_genotype();
private:
    std::vector<int> genotype;
};

#endif //KONKURS_INDIVIDUAL_H