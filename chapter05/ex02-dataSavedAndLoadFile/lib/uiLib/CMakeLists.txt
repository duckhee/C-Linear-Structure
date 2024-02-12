cmake_minimum_required(VERSION 3.2.6)

project(chapter05EX02UILib LANGUAGES C)

message("ui library")

add_library(chapter05EX02UILib STATIC)

target_link_libraries(chapter05EX02UILib PRIVATE Chapter05EX02DataLib)

target_include_directories(chapter05EX02UILib PUBLIC inc)

target_include_directories(chapter05EX02UILib PUBLIC ../dataLib/inc)

target_sources(chapter05EX02UILib PRIVATE src/uiMenu.c)

set_target_properties(chapter05EX02UILib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
