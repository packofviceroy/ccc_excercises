cmake_minimum_required(VERSION 3.5.0)
project(ch13 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(1 1.cpp)
add_executable(2 2.cpp)
add_executable(3 3.cpp)
add_executable(4-5 4-5.cpp)
add_executable(6 6.cpp)


set_property(TARGET 1 2 3 4-5 6 PROPERTY CXX_STANDARD 20)