cmake_minimum_required(VERSION 3.14)
project(ResponseServer C)

set(CMAKE_C_STANDARD 11)

add_executable(ResponseServer main.c broadcast.h broadcast.cpp)