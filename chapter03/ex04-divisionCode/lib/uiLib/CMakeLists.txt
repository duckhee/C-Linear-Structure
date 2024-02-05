cmake_minimum_required(VERSION 3.2.6)

project(uiLib LANGUAGES C)

message("ui library")

add_library(uiLib STATIC)

target_link_libraries(uiLib PRIVATE dataLib)

target_include_directories(uiLib PUBLIC inc)

target_sources(uiLib PRIVATE src/uiMenu.c)

set_target_properties(uiLib PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
