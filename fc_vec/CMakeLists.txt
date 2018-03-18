cmake_minimum_required(VERSION 3.8)
project(fc_vec)

set(CMAKE_CXX_STANDARD 11)

add_executable(fc_vec main.cpp mat/mat.hpp layer.hpp net.hpp utils.hpp solver.hpp activation.hpp)