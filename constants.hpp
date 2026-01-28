//
// Created by mkgrz on 09.01.2026.
//

#ifndef KONKURS_CONSTANTS_H
#define KONKURS_CONSTANTS_H

static constexpr double CROSS_PROB = 0.7;
static constexpr double MUTATION_PROB = 0.1;

static constexpr double WRONG_SOLUTION_ERROR_CODE = -1.0;
static constexpr int FILE_NOT_FOUND_ERROR_CODE = -2;
static constexpr int FILE_LOADED_SUCCESSFULLY = 2;
static constexpr int FILE_LOAD_PROBLEM = -3;
static constexpr int SECTION_NOT_LOADED_INT = -4;
static constexpr std::string SECTION_NOT_LOADED_STRING = "---";

#endif //KONKURS_CONSTANTS_H