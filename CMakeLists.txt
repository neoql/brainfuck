cmake_minimum_required(VERSION 3.9)
project(brainfuck C)

set(CMAKE_C_STANDARD 99)

add_executable(brainfuck main.c brainfuck.c brainfuck.h)

install(TARGETS brainfuck RUNTIME DESTINATION bin)