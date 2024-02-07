cmake_minimum_required(VERSION 3.2.6)

project(ex0401NodeSort LANGUAGES C)

message("ex04-01 all node sort")

add_executable(ex0401NodeSort)

target_sources(ex0401NodeSort PRIVATE main.c)

set_target_properties(ex0401NodeSort PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)