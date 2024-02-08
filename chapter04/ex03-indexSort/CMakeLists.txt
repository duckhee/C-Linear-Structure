cmake_minimum_required(VERSION 3.2.6)

add_subdirectory(lib)

project(ex0403SortByIndex LANGUAGES C)

add_executable(ex0403SortByIndex)

message("ex04-03 sort by index")

target_sources(ex0403SortByIndex PRIVATE main.c)
target_include_directories(ex0403SortByIndex PRIVATE lib/dataLib/inc)
target_include_directories(ex0403SortByIndex PRIVATE lib/uiLib/inc)

target_link_libraries(ex0403SortByIndex PRIVATE Chapter04EX03DataLib)
target_link_libraries(ex0403SortByIndex PRIVATE chapter04EX03UILib)

set_target_properties(ex0403SortByIndex PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)