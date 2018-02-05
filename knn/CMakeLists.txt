cmake_minimum_required(VERSION 3.9)
project(knn)

set(CMAKE_CXX_STANDARD 11)

add_executable(knn main.cpp ./include/knn.h ./src/knn.cpp)