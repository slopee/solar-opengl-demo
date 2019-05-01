cmake_minimum_required(VERSION 3.0)

project(Glitter_tests LANGUAGES CXX VERSION 0.0.1)

include_directories(${CMAKE_SOURCE_DIR}/Glitter/Vendor/catch2)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Glitter/Vendor/catch2/contrib")

#find_package(Catch2 REQUIRED)

add_executable(Glitter_tests ${PROJECT_SOURCE_DIR}/Sources/main.cpp)
target_link_libraries(Glitter_tests Glitter_lib Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(Glitter_tests)
