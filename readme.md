

### Introduction

This is a machine learing library written in c++, which will be updated when i am not busy.

### Armadillo install

This library depends on the popular linear algebra library called armadillo.

To install armalillo on ubuntu, you should install some other library first. Do as described follow:

~~~shell
sudo apt-get install liblapack-dev
sudo apt-get install libblas-dev
sudo apt-get install libboost-dev
~~~

Then install armadillo

~~~shell
sudo apt-get libarmadillo-dev  
~~~



**using armadillo in CLion**

when using armadillo in clion, it need to configure the cmakelists.txt, modified contents is marked by #<<<

~~~cmake
cmake_minimum_required(VERSION 3.3)
project(ThirdProject)

find_package(Armadillo REQUIRED) # <<<
include_directories(${ARMADILLO_INCLUDE_DIRS}) # <<<

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ThirdProject ${SOURCE_FILES})
target_link_libraries(ThirdProject ${ARMADILLO_LIBRARIES}) # <<<
~~~

more details, see:
https://intellij-support.jetbrains.com/hc/en-us/community/posts/205823019-Errors-compiling-code-with-armadillo

