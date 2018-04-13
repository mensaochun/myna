cmake_minimum_required(VERSION 3.8)
project(decision_tree)

set(CMAKE_CXX_STANDARD 11)
#add_executable(decision_tree main.cpp)
add_executable(decision_tree main.cpp decision_tree.h decision_tree.cpp)