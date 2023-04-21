cmake_minimum_required(VERSION 3.23)
project(mandelbrot C)

set(CMAKE_C_STANDARD 17)

add_executable(mandelbrot main.c bmpimg.c bmpimg.h)
