cmake_minimum_required(VERSION 2.8.10)
project (tasks_pool)

include_directories(./include/tpool)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/bin)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory (src) 
add_subdirectory (test)

#enable_testing ()
