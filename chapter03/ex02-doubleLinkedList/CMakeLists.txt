cmake_minimum_required(VERSION 3.2.6)

project(ex0302DoubleLinkedList LANGUAGES C)

add_executable(ex0302DoubleLinkedList)

message("ex03-02 dummy header node double linked list")

target_sources(ex0302DoubleLinkedList PRIVATE main.c)

set_target_properties(ex0302DoubleLinkedList PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)