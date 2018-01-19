cmake_minimum_required(VERSION 2.8)
if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread -fPIC")
        endif ()
else ()
        set (CMAKE_CXX_STANDARD 11)
endif ()

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (
			./src
			${Boost_INCLUDE_DIRS}
                     )


add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (test test.cpp)

target_link_libraries (test
			tp
			${Boost_FILESYSTEM_LIBRARY}
			${Boost_SYSTEM_LIBRARY}
			${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
