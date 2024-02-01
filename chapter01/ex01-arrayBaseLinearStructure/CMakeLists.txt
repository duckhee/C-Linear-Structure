cmake_minimum_required(VERSION 3.2.6)

project(ex01ArrayBaseLinearStructure LANGUAGES C)

message("ex01 array base linear structure")

add_executable(ex01ArrayBaseLinearStructure)

target_sources(ex01ArrayBaseLinearStructure PRIVATE dataStructure.c)

set_target_properties(ex01ArrayBaseLinearStructure PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)