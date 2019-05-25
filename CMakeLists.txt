cmake_minimum_required(VERSION 3.8)
project(HW2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(sequential sequential.cpp sequential.h)
add_executable(parallel parallel.cpp parallel.h)

