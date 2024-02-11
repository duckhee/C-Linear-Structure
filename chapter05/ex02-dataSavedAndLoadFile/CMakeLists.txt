cmake_minimum_required(VERSION 3.2.6)

project(ex0502FileADT LANGUAGES C)

message("ex05-02 data saved file and load file adt")

add_executable(ex0502FileADT)

target_sources(ex0502FileADT PRIVATE main.c)