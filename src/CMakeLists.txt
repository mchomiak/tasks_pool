cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread -fPIC")

include_directories(./include/tpool)

file(GLOB SOURCES "./*.cpp")

add_library(objlibtp OBJECT ${SOURCES})

add_library(tp_shared SHARED $<TARGET_OBJECTS:objlibtp>)
add_library(tp_static STATIC $<TARGET_OBJECTS:objlibtp>)

SET_TARGET_PROPERTIES(tp_shared PROPERTIES OUTPUT_NAME tp CLEAN_DIRECT_OUTPUT 1) 
SET_TARGET_PROPERTIES(tp_static PROPERTIES OUTPUT_NAME tp CLEAN_DIRECT_OUTPUT 1)

#TARGET_LINK_LIBRARIES(tp_shared pthread)





