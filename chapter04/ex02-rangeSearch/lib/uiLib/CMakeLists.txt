cmake_minimum_required(VERSION 3.2.6)

project(chapter04EX02UILib LANGUAGES C)

message("ui library")

add_library(chapter04EX02UILib STATIC)

target_link_libraries(chapter04EX02UILib PRIVATE Chapter04EX02DataLib)

target_include_directories(chapter04EX02UILib PUBLIC inc)

target_sources(chapter04EX02UILib PRIVATE src/uiMenu.c)

set_target_properties(chapter04EX02UILib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
