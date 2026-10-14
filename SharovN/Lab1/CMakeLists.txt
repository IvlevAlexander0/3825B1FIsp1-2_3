cmake_minimum_required(VERSION 3.14)
project(Lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(set STATIC src/tbitfield.cpp src/tset.cpp)
target_include_directories(set PUBLIC include)

add_executable(sample samples/sample_prime_numbers.cpp)
target_link_libraries(sample set)

enable_testing()
add_executable(tests test/test_main.cpp test/test_tbitfield.cpp test/test_tset.cpp)
target_link_libraries(tests set GTest::gtest)
include(GoogleTest)
gtest_discover_tests(tests)
