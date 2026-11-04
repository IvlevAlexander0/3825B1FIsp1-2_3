cmake_minimum_required(VERSION 3.10)
project(Lab1)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

set(INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../includes/Lab1)

add_executable(lab1_test
    main.cpp
    tbitfield.cpp
    tset.cpp
    test_lab1.cpp
    ${INCLUDES_DIR}/tbitfield.h
    ${INCLUDES_DIR}/tset.h
)

target_link_libraries(lab1_test PRIVATE gtest)

target_include_directories(lab1_test PRIVATE
    ${INCLUDES_DIR}
)

include(GoogleTest)
gtest_discover_tests(lab1_test)