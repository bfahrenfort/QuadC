cmake_minimum_required(VERSION 3.16)
project(QuirkTyper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ../bin)

set(SOURCE_FILES src/main.c src/cmd_line.cpp src/cmd_line.h src/quirk.cpp src/quirk.hpp src/color.cpp src/color.hpp)

add_executable(QuirkTyper ${SOURCE_FILES})