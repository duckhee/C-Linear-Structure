cmake_minimum_required(VERSION 3.2.6)

project(ex030301Stack LANGUAGES C)

add_executable(ex030301Stack)

message("ex03-03-01 stack")

target_sources(ex030301Stack PRIVATE main.c)

set_target_properties(ex030301Stack PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)