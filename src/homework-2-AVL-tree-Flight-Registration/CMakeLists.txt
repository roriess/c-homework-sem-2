cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c11")

project(homework-2-AVL-tree-Flight-Registration C)

add_library(operations operations.c)
add_library(tests tests.c)

add_executable(main main.c)

target_link_libraries(main PRIVATE operations tests)
