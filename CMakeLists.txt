cmake_minimum_required(VERSION 3.5)
project(cvector)

include(external/gtest/GTest.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
# dont fall back to an older standard if the compiler doesn't support it
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# disable gnu extensions and similar stuff to get consistent builds
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set(sources vector.c)
set(headers vector.h)
set(test_sources test/vector.cpp)

add_library(cvector ${sources})
target_include_directories(cvector PUBLIC ${CMAKE_CURRENT_LIST_DIR})

create_test(test_cvector SOURCES ${test_sources} DEPENDS cvector)

# add target to run all tests in one executable
if(${CMAKE_PROJECT_NAME}_all_tests)
   create_test_suite(all_tests "${${CMAKE_PROJECT_NAME}_all_tests}")
endif()
