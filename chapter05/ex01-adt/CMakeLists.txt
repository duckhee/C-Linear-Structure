cmake_minimum_required(VERSION 3.2.6)

add_subdirectory(lib)

project(ex0501ADT LANGUAGES C)

message("ex05-01 ADT atKey")

add_executable(ex0501ADT)

target_sources(ex0501ADT PRIVATE main.c)

target_link_libraries(ex0501ADT PRIVATE chapter05EX01UILib)
target_include_directories(ex0501ADT PRIVATE chapter05EX01UILib)
target_link_libraries(ex0501ADT PRIVATE Chapter05EX01DataLib)
target_include_directories(ex0501ADT PRIVATE Chapter05EX01DataLib)

set_target_properties(ex0501ADT PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)