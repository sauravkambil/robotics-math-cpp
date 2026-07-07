cmake_minimum_required(VERSION 3.20)

project(robot_math LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  eigen
  URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(eigen googletest)

add_library(robot_math INTERFACE)

target_include_directories(robot_math
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(robot_math
  INTERFACE
    Eigen3::Eigen
)

enable_testing()

add_executable(test_transform3d
  tests/test_transform3d.cpp
)

target_link_libraries(test_transform3d
  PRIVATE
    robot_math
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_transform3d)