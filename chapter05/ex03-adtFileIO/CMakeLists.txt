cmake_minimum_required(VERSION 3.2.6)

project(ex0503FileADT_IO LANGUAGES C)

message("ex05-03 file adt")

add_executable(ex0503FileADT_IO)

target_sources(ex0503FileADT_IO PRIVATE main.c singleList.c menu.c menu.h singleList.h)

set_target_properties(ex0503FileADT_IO PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
