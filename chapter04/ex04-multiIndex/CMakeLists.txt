cmake_minimum_required(VERSION 3.2.6)

add_subdirectory(lib)

project(ex04MultiIndex LANGUAGES C)

message("ex0404 multi index")

add_executable(ex04MultiIndex)
target_sources(ex04MultiIndex PRIVATE main.c)

target_include_directories(ex04MultiIndex PRIVATE lib/dataLib/inc)
target_include_directories(ex04MultiIndex PRIVATE lib/uiLib/inc)

target_link_libraries(ex04MultiIndex LINK_PRIVATE Chapter04EX04DataLib)
target_link_libraries(ex04MultiIndex LINK_PRIVATE chapter04EX04UILib)

set_target_properties(ex04MultiIndex PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)