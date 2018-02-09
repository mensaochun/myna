cmake_minimum_required(VERSION 3.9)
project(mat)
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(mat mat_array.h mat_vector.h main.cpp)
target_link_libraries(mat ${ARMADILLO_LIBRARIES})