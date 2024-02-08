cmake_minimum_required(VERSION 3.2.6)

project(ex02RangeSearch LANGUAGES C)

add_executable(ex02RangeSearch)

add_subdirectory(lib)

message("ex04-02 range search ")

target_sources(ex02RangeSearch PRIVATE main.c)

target_include_directories(ex02RangeSearch PRIVATE lib/dataLib/inc lib/uiLib/inc)

target_link_libraries(ex02RangeSearch PRIVATE chapter04EX02UILib)

target_link_libraries(ex02RangeSearch PRIVATE Chapter04EX02DataLib)

set_target_properties(ex02RangeSearch PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)