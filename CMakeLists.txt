cmake_minimum_required(VERSION 3.26)
project("Cpp-OpenGL-Template" LANGUAGES CXX C)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)

include(cmake/base/config.cmake)
include(cmake/base/utils.cmake)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

print(CMAKE_BUILD_TYPE)
print(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
print(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
print(CMAKE_RUNTIME_OUTPUT_DIRECTORY)

add_subdirectory("vendor/glad")
add_subdirectory("vendor/glfw")
add_subdirectory("Application")
