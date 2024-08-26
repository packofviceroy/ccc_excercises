cmake_minimum_required(VERSION 3.5.0)
project(ch14 VERSION 0.1.0 LANGUAGES C CXX)


include_directories("/usr/local/include")
include_directories("/usr/local/lib")

add_executable(ch14 book.cpp catch_amalgamated.cpp)

set_property(TARGET ch14 PROPERTY CXX_STANDARD 20)
link_libraries(Catch2)