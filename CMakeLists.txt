cmake_minimum_required(VERSION 3.0)

project(Glitter)

set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Vendor/glad/include/)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Vendor/glfw/include/)
add_subdirectory(Glitter/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
#add_subdirectory(Glitter/Vendor/bullet)

add_subdirectory(Glitter/Vendor/dear-imgui)


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_STANDARD 17)
    add_definitions(-Wall)
    add_definitions(-fno-rtti)
    add_definitions(-D_ENABLE_EXTENDED_ALIGNED_STORAGE)

else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Glitter/Headers/
                    Glitter/Vendor/assimp/include/
#                    Glitter/Vendor/bullet/src/
                    ${GLAD_INCLUDE_DIR}
                    ${GLFW_INCLUDE_DIR}
                    Glitter/Vendor/glm/
                    Glitter/Vendor/stb/
                    Glitter/Vendor/dear-imgui/)

set(VENDORS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Vendor/)
file(GLOB VENDORS_SOURCES ${VENDORS_ROOT}/glad/src/glad.c)
#file(GLOB PROJECT_HEADERS Glitter/Headers/*/*.h*)
#file(GLOB PROJECT_SOURCES Glitter/Sources/*/*.cpp)
set(HEADERS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Headers/App/)
file(GLOB_RECURSE PROJECT_HEADERS Glitter/Headers/App/*.h*)

set(SOURCES_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Sources/App/)
file(GLOB_RECURSE PROJECT_SOURCES Glitter/Sources/App/*.cpp)

set(SHADERS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Shaders/)
file(GLOB PROJECT_SHADERS Glitter/Shaders/*.comp
                          Glitter/Shaders/*.frag
                          Glitter/Shaders/*.geom
                          Glitter/Shaders/*.vert)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group(TREE ${HEADERS_ROOT} PREFIX "Headers" FILES ${PROJECT_HEADERS})
source_group(TREE ${SHADERS_ROOT} PREFIX "Shaders" FILES ${PROJECT_SHADERS})
source_group(TREE ${SOURCES_ROOT} PREFIX "Sources" FILES ${PROJECT_SOURCES})
source_group(TREE ${VENDORS_ROOT} PREFIX "Vendors" FILES ${VENDORS_SOURCES})

# Library (separating project)
add_library(Glitter_lib STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SHADERS})
target_include_directories(Glitter_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Main project
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} Glitter/Sources/main.cpp Glitter/Headers/glitter.hpp
                               ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                    Glitter_lib dear-imgui)
                      #BulletDynamics BulletCollision LinearMath
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Testing
add_subdirectory(Glitter/Vendor/catch2)
add_subdirectory(Glitter/Tests)
enable_testing ()
add_test (NAME tests COMMAND Test)
