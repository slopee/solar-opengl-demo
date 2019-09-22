CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(dear-imgui)

SET (LIB_TYPE STATIC)

file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(dear-imgui ${LIB_TYPE} ${IMGUI_SOURCES} ${IMGUI_HEADERS})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(
    ${IMGUI_HEADERS}
    ${GLAD_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR})

#include_directories(
#    ${IMGUI_INCLUDE_DIR}
#    ${OPENGL_INCLUDE_DIR}
#    ${GLFW_INCLUDE_DIR}
#    ${GLAD_INCLUDE_DIR})

target_link_libraries(dear-imgui glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
#target_link_libraries(dear-imgui
#    ${OPENGL_LIBRARIES}
#    ${GLFW_LIBRARIES}
#    ${GLAD_LIBRARIES})

set_target_properties(dear-imgui PROPERTIES LINKER_LANGUAGE CXX)
#set_target_properties(dearimgui PROPERTIES FOLDER 3rdparty)

set(IMGUI_LIBRARIES dear-imgui)
