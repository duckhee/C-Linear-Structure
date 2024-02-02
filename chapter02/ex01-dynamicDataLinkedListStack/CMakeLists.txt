cmake_minimum_required(VERSION 3.2.6)

project(ex0201DynamicDataLinkedListStack LANGUAGES C)

message("ex02-01 dynamic data linked list")

add_executable(ex0201DynamicDataLinkedListStack)

target_sources(ex0201DynamicDataLinkedListStack PRIVATE dynamicDataLinkedList.c)

set_target_properties(ex0201DynamicDataLinkedListStack PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)
