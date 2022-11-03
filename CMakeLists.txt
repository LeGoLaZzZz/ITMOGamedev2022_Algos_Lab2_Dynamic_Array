cmake_minimum_required(VERSION 3.22)
project(Lab2Array)

set(CMAKE_CXX_STANDARD 14)



add_executable(Lab2Array main.cpp MyArray.cpp MyArray.h)
add_subdirectory(GoogleTests)