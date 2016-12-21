cmake_minimum_required(VERSION 3.5)
project(Expression)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Calculation.cpp
    Expression.cpp
    Expression.h
    Exception.h
    Scanner.h
    start.cpp)

add_executable(Expression ${SOURCE_FILES})