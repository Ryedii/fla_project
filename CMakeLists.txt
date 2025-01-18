cmake_minimum_required(VERSION 3.30)
project(fla_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(fla_project main.cpp
        automata.cpp
        automata.h
        parse.cpp
        parse.h)
