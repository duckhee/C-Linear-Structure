cmake_minimum_required(VERSION 3.2.6)

project(ex0203LinkedListSearch LANGUAGES C)

add_executable(ex0203LinkedListSearch)

message("ex02-03 linked list search")

target_sources(ex0203LinkedListSearch PRIVATE main.c)

set_target_properties(ex0203LinkedListSearch PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)