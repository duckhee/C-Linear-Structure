cmake_minimum_required(VERSION 3.2.6)

project(Chapter05EX01DataLib LANGUAGES C)

message("data structure lib -> stack and queue")

add_library(Chapter05EX01DataLib STATIC)

target_include_directories(Chapter05EX01DataLib PUBLIC inc)

target_sources(Chapter05EX01DataLib PRIVATE src/dataList.c)


set_target_properties(Chapter05EX01DataLib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
