cmake_minimum_required(VERSION 2.8.10)
project (tasks_pool)
include_directories(./src)

file(GLOB SOURCES "./src/*.cpp")
add_executable(./build/tp ${SOURCES})
