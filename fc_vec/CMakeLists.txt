cmake_minimum_required(VERSION 3.8)
project(fc_vec)

set(CMAKE_CXX_STANDARD 11)
FILE(GLOB_RECURSE SRC_LIST /home/pi/stone/c++/myna/fc_vec "*.cpp" "*.hpp")
#FILE(GLOB_RECURSE SRC_LIST "main.cpp" "./dataType/test_vec.hpp" "./dataType/common.hpp" "./dataType/vector.hpp")
add_executable(fc_vec ${SRC_LIST} )