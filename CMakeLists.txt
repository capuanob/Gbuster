# Set up CMakeLists
cmake_minimum_required(VERSION 3.16)
project(Gbuster)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE) # Used for mixing libraries into 1 executable

enable_testing()
add_subdirectory(src)