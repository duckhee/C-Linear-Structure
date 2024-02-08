cmake_minimum_required(VERSION 3.2.6)

project(chapter04EX04UILib LANGUAGES C)

message("ui library")

add_library(chapter04EX04UILib STATIC)

target_link_libraries(chapter04EX04UILib PRIVATE Chapter04EX03DataLib)

target_include_directories(chapter04EX04UILib PUBLIC inc)

target_include_directories(chapter04EX04UILib PUBLIC ../dataLib/inc)

target_sources(chapter04EX04UILib PRIVATE src/uiMenu.c)

set_target_properties(chapter04EX04UILib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
