cmake_minimum_required(VERSION 3.2.6)

project(ex0103PrintMenu LANGUAGES C)

message("ex01-03 print menu")

add_executable(ex0103PrintMenu)

target_sources(ex0103PrintMenu PRIVATE ui.c)

set_target_properties(ex0103PrintMenu PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)