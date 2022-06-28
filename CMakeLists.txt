cmake_minimum_required(VERSION 3.20)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
project(address_normilzer)

add_library(parser parser.cpp)
target_include_directories(parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/boost_1_79_0)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    parser_test
    test.cpp
    )
target_include_directories(parser_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/boost_1_79_0)
target_link_libraries(parser_test gtest_main parser)
include(GoogleTest)
gtest_discover_tests(parser_test)
