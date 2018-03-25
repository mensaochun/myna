cmake_minimum_required(VERSION 3.8)
project(fc_vec)

set(CMAKE_CXX_STANDARD 11)
FILE(GLOB_RECURSE SRC_LIST1 "./dataType/*.hpp")
FILE(GLOB_RECURSE SRC_LIST2 "./networkComponent/*.hpp")
FILE(GLOB SRC_LIST3 "main.cpp")
add_executable(fc_vec ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST3})