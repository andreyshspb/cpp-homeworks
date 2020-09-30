cmake_minimum_required(VERSION 3.10)
project(lab_13)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories("include")

add_executable(lab_13 src/main.cpp include/my_array.h include/my_array_impl
               include/Product.hpp src/Product.cpp)
