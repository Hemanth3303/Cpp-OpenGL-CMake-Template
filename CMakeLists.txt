cmake_minimum_required(VERSION 3.26)
project("Cpp-OpenGL-Template" LANGUAGES CXX C)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)

include(cmake/base/core/core.cmake)
include(cmake/base/utils/print_vars.cmake)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

print_var(CMAKE_BUILD_TYPE)
print_var(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
print_var(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
print_var(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
print_var(CMAKE_INSTALL_PREFIX)

add_subdirectory("vendor/glad")
add_subdirectory("vendor/glfw")
add_subdirectory("Application")
