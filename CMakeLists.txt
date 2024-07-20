cmake_minimum_required(VERSION 3.26)

project("Cpp-OpenGL-Template" LANGUAGES CXX C)

# Set the available build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "Limited Configs" FORCE)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)

include(cmake/print.cmake)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

if(MSVC)
	add_compile_options(/EHsc)
endif()

print(CMAKE_BUILD_TYPE)


# Use the generator expression $<0:> so that the specified folder is used directly, without any configuration-dependent suffix.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")

print(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
print(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
print(CMAKE_RUNTIME_OUTPUT_DIRECTORY)

add_subdirectory("vendor/glad")
add_subdirectory("vendor/glfw")
add_subdirectory("Application")