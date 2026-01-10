cmake_minimum_required(VERSION 4.1)
project(konkurs)

set(CMAKE_CXX_STANDARD 17)

add_executable(konkurs main.cpp
        individual.cpp
        individual.h
        evaluator.cpp
        evaluator.h
        constants.h
        smart_pointer/my_smart_pointer.h
        smart_pointer/ref_counter.h
        problem.cpp
        problem.h)
