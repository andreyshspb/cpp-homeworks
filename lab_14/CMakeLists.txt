cmake_minimum_required(VERSION 3.10)
project(lab_14)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(lab_14 src/main.cpp include/matrix.hpp src/matrix.cpp)
