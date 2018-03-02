cmake_minimum_required(VERSION 3.9)
project(linear_regression)

set(CMAKE_CXX_STANDARD 11)

add_executable(linear_regression main.cpp linear_regression.h linear_regression.cpp)