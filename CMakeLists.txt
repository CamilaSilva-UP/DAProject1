cmake_minimum_required(VERSION 3.30)
project(DAProjectClion)

set(CMAKE_CXX_STANDARD 20)

add_executable(DAProjectClion main.cpp
        dijkstra.cpp
        csvparsing.cpp
        csvparsing.h
        RoutePlanner.cpp
        dijkstra_alt.cpp
        RoutePlanner.h
        batchMode.cpp
        batchMode.h
        dijkstra.h
        dijkstra_alt.h)
