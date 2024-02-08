cmake_minimum_required(VERSION 3.2.6)

project(chapter04EX03UILib LANGUAGES C)

message("ui library")

add_library(chapter04EX03UILib STATIC)

target_link_libraries(chapter04EX03UILib PRIVATE Chapter04EX03DataLib)

target_include_directories(chapter04EX03UILib PUBLIC inc)

target_sources(chapter04EX03UILib PRIVATE src/uiMenu.c)

set_target_properties(chapter04EX03UILib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
