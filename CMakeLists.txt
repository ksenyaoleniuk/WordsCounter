cmake_minimum_required(VERSION 3.6)
project(WordsCounter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp test.cpp test.h)
add_executable(WordsCounter ${SOURCE_FILES})