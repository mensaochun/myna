cmake_minimum_required(VERSION 3.8)
project(fc_vec)

set(CMAKE_CXX_STANDARD 11)

add_executable(fc_vec main.cpp ./mat/mat.h ./mat/mat.cpp mat/test_mat.cpp)# layer.h net.h utils.h layer.cpp net.cpp solver.h solver.cpp activation.cpp activation.h )