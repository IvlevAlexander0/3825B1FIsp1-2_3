cmake_minimum_required(VERSION 3.24)
project(Lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab2_tests test/test_tvector.cpp test/test_tmatrix.cpp)
target_include_directories(lab2_tests PRIVATE include)
target_link_libraries(lab2_tests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(lab2_tests)
