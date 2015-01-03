cmake_minimum_required(VERSION 2.6)

# Configurable.

project(filter-iterator CXX)
set(project_lib "libfilter_iterator")

option(FILTER_ITERATOR_ENABLE_TESTS
	"Enables or disables tests. Disabled by default." OFF)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}.")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fstack-protector")
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Wextra -Werror -pedantic")


set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE src_files "${src_dir}/*.cpp")

set(FILTER_ITERATOR_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${FILTER_ITERATOR_INCLUDE_DIRS})


if (FILTER_ITERATOR_ENABLE_TESTS)
	add_subdirectory(test)
endif()
