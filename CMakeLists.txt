cmake_minimum_required(VERSION 4.1)
project(konkurs)

set(CMAKE_CXX_STANDARD 17)

add_executable(konkurs main.cpp
        individual.cpp
        individual.hpp
        evaluator/evaluator_implementation.cpp
        evaluator/evaluator_implementation.hpp
        constants.hpp
        smart_pointer/my_smart_pointer.hpp
        smart_pointer/ref_counter.hpp
        problem.cpp
        problem.hpp
        genetic_algorithm.cpp
        genetic_algorithm.hpp
        evaluator/evaluator_implementation.cpp
        evaluator/evaluator_implementation.hpp
)
