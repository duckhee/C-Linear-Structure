cmake_minimum_required(VERSION 3.2.6)

project(ex04DivisionInterest LANGUAGES C)

add_subdirectory(lib)

message("ex04-division interest code")

add_executable(ex04DivisionInterest)

target_sources(ex04DivisionInterest PRIVATE main.c)

target_link_libraries(ex04DivisionInterest PRIVATE uiLib)

target_link_libraries(ex04DivisionInterest PRIVATE dataLib)

set_target_properties(ex04DivisionInterest PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)