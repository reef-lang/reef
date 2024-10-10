cmake_minimum_required(VERSION 3.30.3)

project(Reef VERSION 1.0.0 DESCRIPTION "An experimental, high-level, statically typed compiled programming language designed for performance and reliability." LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Including GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add lexer tests
add_executable(lexer_test ../tests/lexer/lexer_test.cpp)
target_link_libraries(lexer_tests GTest::gtest_main)

# Discover tests
include(GoogleTest)
gtest_discover_tests(lexer_tests)