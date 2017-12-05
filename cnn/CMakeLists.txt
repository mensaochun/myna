cmake_minimum_required(VERSION 3.8)
project(cnn)

find_package(Armadillo REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp include/blob.h src/blob.cpp)
add_executable(cnn ${SOURCE_FILES})
target_link_libraries(cnn ${ARMADILLO_LIBRARIES})
