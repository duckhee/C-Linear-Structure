cmake_minimum_required(VERSION 3.2.6)

project(ex030302Queue LANGUAGES C)

add_executable(ex030302Queue)

message("ex03-03-02 queue")

target_sources(ex030302Queue PRIVATE main.c)

set_target_properties(ex030302Queue PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)