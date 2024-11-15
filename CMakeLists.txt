cmake_minimum_required(VERSION 3.14)
project(Instrumentpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(instrumentpp STATIC
    ${SRC_DIR}/instrument.cpp
)
target_include_directories(instrumentpp PUBLIC ${SRC_DIR})

add_executable(example_1 examples/example_1.cpp)
target_link_libraries(example_1 PRIVATE instrumentpp)