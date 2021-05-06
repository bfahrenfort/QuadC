cmake_minimum_required(VERSION 3.16)
project(QuirkTyper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ../bin)

set(SOURCE_FILES src/main.cpp src/quirk.hpp src/quirk.cpp src/color.cpp src/color.hpp)

add_executable(QuirkTyper ${SOURCE_FILES})