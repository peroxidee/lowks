cmake_minimum_required(VERSION 3.28)
project(lowks C)

set(CMAKE_C_STANDARD 11)

add_executable(lowks main.c
        lowkey.h)
