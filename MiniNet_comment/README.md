建立`MiniNet`工程，在该工程下，建立`include`文件夹、`src`文件夹和`main.cpp`文件，然后配置`CMakeLists.txt`

~~~cmake
cmake_minimum_required(VERSION 3.8)
project(cnn)
set(CMAKE_CXX_STANDARD 11)

# armadillo
find_package(Armadillo REQUIRED)
#[NOT NECESSARY] include_directories(${ARMADILLO_INCLUDE_DIRS})
# Add the source in project root directory
aux_source_directory(. DIRSRCS)
# Add header file include directories
include_directories(./include)
# Add block directories
add_subdirectory(./src)
# Target
add_executable(cnn ${DIRSRCS})
target_link_libraries(cnn  src ${ARMADILLO_LIBRARIES} libjson_linux-gcc-4.8_libmt.so )
~~~

