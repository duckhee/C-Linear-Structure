cmake_minimum_required(VERSION 3.2.6)

project(ex0201BinaryModeSave)

message("ex02-01 binary mode save")

add_executable(ex0201BinaryModeSave)

target_sources(ex0201BinaryModeSave PRIVATE main.c)

set_target_properties(ex0201BinaryModeSave PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)