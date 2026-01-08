cmake_minimum_required(VERSION 4.1)
project(konkurs)

set(CMAKE_CXX_STANDARD 17)

add_executable(konkurs main.cpp
        individual.cpp
        individual.h)
