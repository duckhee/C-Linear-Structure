cmake_minimum_required(VERSION 3.2.6)

project(LectureCode LANGUAGES C)

message("lecture code example")

add_executable(LectureCode)

target_sources(LectureCode PRIVATE main.c)

set_target_properties(LectureCode PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)