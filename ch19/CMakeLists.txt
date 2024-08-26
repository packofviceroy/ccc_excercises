cmake_minimum_required(VERSION 3.25)
project(ch19)

set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

add_executable(ch19 main.cpp)
