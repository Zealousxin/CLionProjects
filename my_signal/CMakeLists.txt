cmake_minimum_required(VERSION 3.17)
project(my_signal C)

set(CMAKE_C_STANDARD 99)

add_executable(my_signal test_settimer.c sigsetjmp.c)