cmake_minimum_required(VERSION 3.2.6)

project(Chapter04EX03DataLib LANGUAGES C)

message("data structure lib -> stack and queue")

add_library(Chapter04EX03DataLib STATIC)

target_include_directories(Chapter04EX03DataLib PUBLIC inc)

target_sources(Chapter04EX03DataLib PRIVATE src/dataList.c)


set_target_properties(Chapter04EX03DataLib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
