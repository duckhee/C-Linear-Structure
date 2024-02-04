cmake_minimum_required(VERSION 3.2.6)

project(ex0301DummyHeadNodeLinkedList LANGUAGES C)

add_executable(ex0301DummyHeadNodeLinkedList)

message("ex03-01 dummy header node linked list")

target_sources(ex0301DummyHeadNodeLinkedList PRIVATE main.c)

set_target_properties(ex0301DummyHeadNodeLinkedList PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)