![icon](./pics/icon.png)

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

when using armadillo in clion, it need to configure the cmakelists.txt, there are several ways to do this.

Method 1:

 add  contents  marked by #<<<

~~~cmake
cmake_minimum_required(VERSION 3.3)
project(ThirdProject)

find_package(Armadillo REQUIRED) # <<<
include_directories(${ARMADILLO_INCLUDE_DIRS}) # <<< it is optional if armadillo include folder is put in /usr/include.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ThirdProject ${SOURCE_FILES})
target_link_libraries(ThirdProject ${ARMADILLO_LIBRARIES}) # <<<
~~~

more details, see:
https://intellij-support.jetbrains.com/hc/en-us/community/posts/205823019-Errors-compiling-code-with-armadillo

Method 2: note that libarmadillo.so.4.200.0 and libarmadillo.so.7.500.2 must specify the absolute path, otherwise it will not be found, not known why so far.

~~~cmake
cmake_minimum_required(VERSION 3.8)
project(xxtest)

set(CMAKE_CXX_STANDARD 11)
link_libraries("libarmadillo.so")
link_libraries("libarmadillo.so.4")
link_libraries("/usr/lib/libarmadillo.so.4.200.0")
link_libraries("libarmadillo.so.7")
link_libraries("/usr/lib/libarmadillo.so.7.500.2")

set(SOURCE_FILES main.cpp)
add_executable(xxtest ${SOURCE_FILES})
~~~



