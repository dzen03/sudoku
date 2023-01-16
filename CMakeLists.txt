cmake_minimum_required(VERSION 3.23)
project(sudoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(sudoku main.cpp sudoku.cpp sudoku.h)
