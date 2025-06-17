# Top Level CMakeLists
#--------------------------------------------------------#
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
PROJECT(khwarizmi_engine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)  # pick a high number; compiler picks the highest it knows
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Use strict standard, no compiler extensions

# Set Khawarzimi Engine version
set(LibKE_VERSION ${PROJECT_VERSION})

# Add sub directories for sub projects.
add_subdirectory(variant_lib)
add_subdirectory(khwarizmi_engine)

#--------------------------------------------------------#