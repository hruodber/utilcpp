cmake_minimum_required(VERSION 3.26)
project(utilcpp)


set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(utilcpp main.cpp src/pbPlots.cpp src/supportLib.cpp)
