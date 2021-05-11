cmake_minimum_required(VERSION 3.16)
project(QuirkTyper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ../bin)

set(SOURCE_FILES src/dialog.cpp src/dialog.h src/resource.h src/dialog.rc # Winapi files
                 src/cmd_line.cpp src/cmd_line.h # Command line files
                 src/main.c src/quirk.cpp src/quirk.hpp src/color.cpp src/color.hpp) # Common files

add_executable(QuirkTyper WIN32 ${SOURCE_FILES})