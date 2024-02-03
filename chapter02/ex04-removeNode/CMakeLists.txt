cmake_minimum_required(VERSION 3.2.6)

project(ex0204RemoveNode LANGUAGES C)

add_executable(ex0204RemoveNode)

message("ex02-04 remove node")

target_sources(ex0204RemoveNode PRIVATE main.c)

set_target_properties(ex0204RemoveNode PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)