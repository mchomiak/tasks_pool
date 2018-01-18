cmake_minimum_required(VERSION 2.8.10)
project (tasks_pool)
# add_subdirectory(src)

if (CMAKE_VERSION VERSION_LESS "3.1")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")
	endif ()
else ()
	set (CMAKE_CXX_STANDARD 11)
endif ()

include_directories(./src)

file(GLOB SOURCES "./src/*.cpp")
set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY
${CMAKE_HOME_DIRECTORY}/build
)
add_executable(tp ${SOURCES})
TARGET_LINK_LIBRARIES(tp pthread)

