cmake_minimum_required(VERSION 3.22)
project(cmplx C)

set(CMAKE_C_STANDARD 17)


add_executable(cmplx main.c bmpimg.c bmpimg.h)

target_link_libraries(cmplx -lm)