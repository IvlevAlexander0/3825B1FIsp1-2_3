cmake_minimum_required(VERSION 3.10)
project(Lab1)
set(CMAKE_CXX_STANDARD 17)

# Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(lab1_test
    main.cpp
    tbitfield.cpp
    tset.cpp
    test_lab1.cpp
)

target_link_libraries(lab1_test PRIVATE gtest gtest_main)
target_include_directories(lab1_test PRIVATE .)