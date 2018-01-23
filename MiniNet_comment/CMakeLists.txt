cmake_minimum_required(VERSION 3.9)
project(MiniNet_comment)
find_package(Armadillo REQUIRED) # <<<
include_directories(${ARMADILLO_INCLUDE_DIRS}) # <<<
set(CMAKE_CXX_STANDARD 11)

add_executable(MiniNet_comment main.cpp include/blob.hpp include/layer.hpp include/mini_net.hpp include/net.hpp include/test.hpp
        src/blob.cpp src/layer.cpp src/net.cpp)
target_link_libraries(MiniNet_comment ${ARMADILLO_LIBRARIES} libjson_linux-gcc-4.8_libmt.so) # <<<