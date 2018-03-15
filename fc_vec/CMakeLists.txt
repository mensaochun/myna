cmake_minimum_required(VERSION 3.9)
project(fc_vec)

set(CMAKE_CXX_STANDARD 11)

add_executable(fc_vec main.cpp mat.h layer.h net.h utils.h layer.cpp net.cpp)