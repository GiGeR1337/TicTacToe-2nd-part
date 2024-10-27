cmake_minimum_required(VERSION 3.27)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_library(TicTacToe SHARED library.cpp
        Main.cpp)

target_link_options(TicTacToe PRIVATE "-static")

target_include_directories(TicTacToe PRIVATE "C:/Users/danyl/.jdks/openjdk-23.0.1/include")
target_include_directories(TicTacToe PRIVATE "C:/Users/danyl/.jdks/openjdk-23.0.1/include/win32")