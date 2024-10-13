# Top Level CMakeLists
#--------------------------------------------------------#
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
PROJECT(khwarizmi_engine VERSION 0.0.1)

# Set IntelligentTuringAnimation version
set(LibKE_VERSION ${PROJECT_VERSION})

# Add sub directories for sub projects.
add_subdirectory(khwarizmi_engine)
#--------------------------------------------------------#