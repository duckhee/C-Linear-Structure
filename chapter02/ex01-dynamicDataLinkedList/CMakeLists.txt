cmake_minimum_required(VERSION 3.2.6)

project(ex0201DynamicDataLinkedList LANGUAGES C)

message("ex02-01 dynamic data linked list")

add_executable(ex0201DynamicDataLinkedList)

target_sources(ex0201DynamicDataLinkedList PRIVATE dynamicDataLinkedList.c)

set_target_properties(ex0201DynamicDataLinkedList PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
