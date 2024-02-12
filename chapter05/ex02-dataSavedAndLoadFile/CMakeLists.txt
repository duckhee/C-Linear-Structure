cmake_minimum_required(VERSION 3.2.6)

project(ex0502FileADT LANGUAGES C)

add_subdirectory(lib)

message("ex05-02 data saved file and load file adt")

add_executable(ex0502FileADT)

target_sources(ex0502FileADT PRIVATE main.c)

target_link_libraries(ex0502FileADT LINK_PRIVATE chapter05EX02UILib)
target_include_directories(ex0502FileADT PRIVATE lib/uiLib/inc)
target_link_libraries(ex0502FileADT LINK_PRIVATE Chapter05EX02DataLib)
target_include_directories(ex0502FileADT PRIVATE lib/dataLib/inc)

set_target_properties(ex0502FileADT PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)