cmake_minimum_required(VERSION 3.2.6)

project(Chapter05EX02DataLib LANGUAGES C)

message("data structure lib -> stack and queue")

add_library(Chapter05EX02DataLib STATIC)

target_include_directories(Chapter05EX02DataLib PUBLIC inc)

target_sources(Chapter05EX02DataLib PRIVATE src/dataList.c)


set_target_properties(Chapter05EX02DataLib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
