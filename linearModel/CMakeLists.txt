cmake_minimum_required(VERSION 3.8)
project(linearModel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp LinearRegression.h matrix.h)
add_executable(linearModel ${SOURCE_FILES})