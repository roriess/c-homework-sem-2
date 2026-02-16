cmake_minimum_required(VERSION 3.15)

project(homework-1-CSV C)

add_library(operations operations.c)

add_executable(main main.c)

target_link_libraries(main PRIVATE operations)
