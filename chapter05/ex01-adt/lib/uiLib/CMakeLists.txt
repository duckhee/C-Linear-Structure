cmake_minimum_required(VERSION 3.2.6)

project(chapter05EX01UILib LANGUAGES C)

message("ui library")

add_library(chapter05EX01UILib STATIC)

target_link_libraries(chapter05EX01UILib PRIVATE Chapter05EX01DataLib)

target_include_directories(chapter05EX01UILib PUBLIC inc)

target_include_directories(chapter05EX01UILib PUBLIC ../dataLib/inc)

target_sources(chapter05EX01UILib PRIVATE src/uiMenu.c)

set_target_properties(chapter05EX01UILib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
