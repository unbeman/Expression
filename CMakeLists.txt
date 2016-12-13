cmake_minimum_required(VERSION 3.6)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Expression.h Expression.cpp start.cpp Scanner.cpp Scanner.h)
add_executable(Calculator ${SOURCE_FILES})
