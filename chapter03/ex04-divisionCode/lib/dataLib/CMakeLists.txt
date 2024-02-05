cmake_minimum_required(VERSION 3.2.6)

project(dataLib LANGUAGES C)

message("data structure lib -> stack and queue")

add_library(dataLib STATIC)

target_include_directories(dataLib PUBLIC inc)

target_sources(dataLib PRIVATE src/dataList.c )


set_target_properties(dataLib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
