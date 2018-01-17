cmake_minimum_required(VERSION 2.8.10)
project (tasks_pool)
# add_subdirectory(src)
add_compile_options(-std=c++11)
include_directories(./src)

file(GLOB SOURCES "./src/*.cpp")
set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY
${CMAKE_HOME_DIRECTORY}/build
)
add_executable(tp ${SOURCES})
