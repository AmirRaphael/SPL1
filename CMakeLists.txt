cmake_minimum_required(VERSION 3.17)
project(SPL1)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(SPL1
        Agent.h
        Graph.cpp
        Graph.h
        main.cpp
        Session.h
        Tree.h)
