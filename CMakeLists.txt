cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-grapheditor)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Various / Dependencies
# ------------------------------------------------------------------------------
include("CMake/AddCompilerFlags.cmake")
include("CMake/AddDependencies.cmake")


# ------------------------------------------------------------------------------
# GraphEditor Executable
# ------------------------------------------------------------------------------
message(STATUS "Building GraphEditor client")
include("CMake/AddGrapheditor.cmake") #TODO


