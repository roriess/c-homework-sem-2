cmake_minimum_required(VERSION 3.15)
project(ForClangTidyWork C)

add_library(forClangTidyWork forClangTidyWork.c)

add_executable(main main.c)

target_link_libraries(main PRIVATE forClangTidyWork)
