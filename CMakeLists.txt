cmake_minimum_required(VERSION 3.14)
project(test_project)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

set(FUNCTIONS 
            functions.cpp
            functions.hpp
            )

add_library(functions ${FUNCTIONS})
add_executable(main main.cpp)
add_executable(test test.cpp)

target_link_libraries(main functions)
target_link_libraries(test Boost::unit_test_framework functions)