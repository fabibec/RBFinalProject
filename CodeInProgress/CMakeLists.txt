cmake_minimum_required(VERSION 3.25)
project(CodeInProgress C)

set(CMAKE_C_STANDARD 11)

add_executable(CodeInProgress
        main.c debug.c types.h utils.c)
