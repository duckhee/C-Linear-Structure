cmake_minimum_required(VERSION 3.2.6)

project(ex0202DynamicDataLinkedListQueue LANGUAGES C)

message("ex02-02 dynamic linked list queue")

add_executable(ex0202DynamicDataLinkedListQueue)

target_sources(ex0202DynamicDataLinkedListQueue PRIVATE main.c)

set_target_properties(ex0202DynamicDataLinkedListQueue PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)