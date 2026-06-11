cmake_minimum_required(VERSION 4.2)
project(untitled C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled main.c
        utils.c
        utils.h
        file_io.c
        file_io.h
        text_ops.c
        text_ops.h
        text_ops.c
        history.c
        history.h
)
