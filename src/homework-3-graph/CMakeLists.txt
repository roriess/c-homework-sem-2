cmake_minimum_required(VERSION 3.15)
project(Homework-3-graph C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")

add_executable(main main.c graph.c dijkstra.c heap.c)

add_executable(tests tests.c graph.c dijkstra.c heap.c)

target_include_directories(main PRIVATE src)
target_include_directories(tests PRIVATE src)
